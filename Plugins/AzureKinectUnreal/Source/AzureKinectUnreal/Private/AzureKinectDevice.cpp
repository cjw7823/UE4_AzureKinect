// Fill out your copyright notice in the Description page of Project Settings.


#include "AzureKinectDevice.h"
#include "Containers/Ticker.h"
#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY(AzureKinectDeviceLog);

AzureKinectDevice::AzureKinectDevice() :
	AzureKinectDevice(0, 0, EKinectRemap::COLOR_TO_DEPTH)
{
}

AzureKinectDevice::AzureKinectDevice(int32 Id, int32 TimeOut, EKinectRemap remap) :
	DepthTexture(nullptr),
	ColorTexture(nullptr),
	InflaredTexture(nullptr),
	BodyIndexTexture(nullptr),
	RemapMode(remap),
	NativeKinectDevice(nullptr),
	DeviceId(Id),
	NativeBodyTracker(nullptr),
	TimeOutInMilliSecs(TimeOut),
	Thread(nullptr),
	bIsInitialized(false),
	bShowAllLogs(false),
	bShowOnScreenMsgs(false)
{
	TimeOutInMilliSecsConverted = std::chrono::milliseconds(TimeOutInMilliSecs);
}

AzureKinectDevice::~AzureKinectDevice()
{
	Shutdown();
}

bool AzureKinectDevice::Initialize(k4a_depth_mode_t DepthMode, k4a_color_resolution_t ColorMode)
{
	try
	{
		// Open the Azure Kinect Device
		NativeKinectDevice = k4a::device::open(DeviceId);

		// Start the Camera and make sure the Depth Camera is Enabled
		k4a_device_configuration_t deviceConfig = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
		deviceConfig.depth_mode = DepthMode;
		deviceConfig.color_resolution = ColorMode;

		if (ColorMode != K4A_COLOR_RESOLUTION_OFF)
		{
			deviceConfig.color_format = k4a_image_format_t::K4A_IMAGE_FORMAT_COLOR_BGRA32;
			deviceConfig.synchronized_images_only = true;
		}
		
		NativeKinectDevice.start_cameras(&deviceConfig);

		// Get the device calibration
		k4a::calibration sensorCalibration = NativeKinectDevice.get_calibration(deviceConfig.depth_mode, deviceConfig.color_resolution);
		KinectTransformation = k4a::transformation(sensorCalibration);

		// Create the Body tracker using the calibration
		NativeBodyTracker = k4abt::tracker::create(sensorCalibration);



	}
	catch (k4a::error initError)
	{
		FString initErrorStr(initError.what());
		UE_LOG(AzureKinectDeviceLog, Error, TEXT("Kinect device (id : %d) - Initialization Failed with error : %s"), DeviceId, *initErrorStr);
		return false;
	}

	bIsInitialized = true;

	InitializeBodies();
	StartKinectThread();

	TickHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &AzureKinectDevice::OnTick), TickInterval);

	return true;
}

void AzureKinectDevice::Shutdown()
{
	bIsInitialized = false;

	if (Thread)
	{
		Thread->Shutdown();
		Thread = nullptr;
	}

	FTicker::GetCoreTicker().RemoveTicker(TickHandle);

	for (UAzureKinectBody *body : Bodies)
	{
		body->RemoveFromRoot();
	}
	Bodies.Empty();

	if (NativeBodyTracker)
	{
		NativeBodyTracker.shutdown();
		NativeBodyTracker.destroy();
		NativeBodyTracker = nullptr;
		UE_LOG(AzureKinectDeviceLog, Warning, TEXT("BodyTracker Shutdown and Destroyed"));
	}

	if (NativeKinectDevice)
	{
		NativeKinectDevice.stop_cameras();
		NativeKinectDevice.close();
		NativeKinectDevice = nullptr;
		UE_LOG(AzureKinectDeviceLog, Warning, TEXT("KinectDevice Camera is Stopped and Closed"));
	}

	if (RemapImage)
	{
		RemapImage.reset();
	}
}

void AzureKinectDevice::CaptureBodyTrackingFrame()
{
	if (!bIsInitialized)
	{
		UE_LOG(AzureKinectDeviceLog, Error, TEXT("Kinect device for capturing body tracking frame is Not Initialized!"));
		return;
	}

	if (!NativeKinectDevice)
	{
		UE_LOG(AzureKinectDeviceLog, Error, TEXT("Kinect device for capturing body tracking frame is Invalid!"));
		return;
	}

	if (!NativeBodyTracker)
	{
		UE_LOG(AzureKinectDeviceLog, Error, TEXT("Body Tracker for capturing body tracking frame is Invalid!"));
		return;
	}

	uint32_t i = 0;
	try
	{
		// Capture a depth frame
		k4a::capture sensorCapture = nullptr;
		if (!NativeKinectDevice.get_capture(&sensorCapture, TimeOutInMilliSecsConverted))
		{
			UE_CLOG(bShowAllLogs, AzureKinectDeviceLog, Error, TEXT("Kinect device get capture Timed Out!"));
			return;
		}
		Capture = sensorCapture;

		// Enqueue the capture
		if (!NativeBodyTracker.enqueue_capture(sensorCapture, TimeOutInMilliSecsConverted))
		{
			UE_CLOG(bShowAllLogs, AzureKinectDeviceLog, Error, TEXT("Adding capture to the Tracker process queue Timed Out!"));
			return;
		}

		k4abt::frame bodyFrame = nullptr;
		if (!NativeBodyTracker.pop_result(&bodyFrame, TimeOutInMilliSecsConverted))
		{
			UE_CLOG(bShowAllLogs, AzureKinectDeviceLog, Error, TEXT("Tracker pop body frame result Timed Out!"));
			return;
		}

		// Successfully popped the body tracking result
		uint32_t numBodies = bodyFrame.get_num_bodies();
		if (GEngine && bShowOnScreenMsgs)
		{
			GEngine->AddOnScreenDebugMessage(0, 5.0f, (numBodies > 0 ? FColor::Cyan : FColor::Red), FString::Printf(TEXT("%zu bodies are detected"), numBodies));
		}

		// Get the skeleton data for the tracked bodies
		for (; i < FMath::Min(numBodies, MaxBodies); i++)
		{
			k4abt_body_t body;
			try
			{
				bodyFrame.get_body_skeleton(i, body.skeleton);
			}
			catch (k4a::error skeletonError)
			{
				UE_CLOG(bShowAllLogs, AzureKinectDeviceLog, Error, TEXT("Get Body Skeleton Failed!"));
				Bodies[i]->bIsTracked = false;
				continue;
			}

			body.id = bodyFrame.get_body_id(i);

			if (GEngine && bShowOnScreenMsgs)
			{
				GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Cyan, FString::Printf(TEXT("  Body Id : %d"), body.id));
			}

			Bodies[i]->NativeBody = body;
			Bodies[i]->bIsTracked = true;
		}

		// Set all the remaining Bodies to be Not tracked
		for (uint32 j = i; j < MaxBodies; j++)
		{
			Bodies[j]->bIsTracked = false;
		}

		//렌더링 할 캡쳐 데이터는 MasterDevice에서만 추출한다.
		if (DeviceId == 0)
		{
			if (ColorTexture)
			{
				CaptureColorImage();
			}

			if (DepthTexture)
			{
				CaptureDepthImage();
			}

			if (InflaredTexture)
			{
				CaptureInflaredImage();
			}

			if (BodyIndexTexture)
			{
				CaptureBodyIndexImage(bodyFrame);
			}
		}
	}
	catch (k4a::error captureError)
	{
		FString captureErrorStr(captureError.what());
		UE_CLOG(bShowAllLogs, AzureKinectDeviceLog, Error, TEXT("Kinect device body tracking capture Failed with error : %s"), *captureErrorStr);
	}

}

int32 AzureKinectDevice::GetTimeOutInMilliSecs() const
{
	return TimeOutInMilliSecs;
}

TArray<UAzureKinectBody*> AzureKinectDevice::GetBodies() const
{
	return Bodies;
}

bool AzureKinectDevice::IsInitialized() const
{
	return bIsInitialized;
}

void AzureKinectDevice::InitializeBodies()
{
	// reset any allocated memory
	Bodies.Empty(MaxBodies);
	Bodies.SetNum(MaxBodies);
	Bodies.Shrink();

	for (uint32 i = 0; i < MaxBodies; i++)
	{
		Bodies[i] = NewObject<UAzureKinectBody>();
		Bodies[i]->AddToRoot();
	}
}

void AzureKinectDevice::StartKinectThread()
{
	Thread = FAzureKinectThread::InitPolling(this);
}

bool AzureKinectDevice::OnTick(float DeltaTime)
{
	if (bIsInitialized)
	{
		for (UAzureKinectBody *Body : Bodies)
		{
			Body->UpdateBodyWithKinectInfo();
		}
	}

	return true;
}

void AzureKinectDevice::ToggleShowLogsAndOnScreenMsgs(bool ShouldShowLogs, bool ShouldShowOnScreenMsgs)
{
	bShowAllLogs = ShouldShowLogs;
	bShowOnScreenMsgs = ShouldShowOnScreenMsgs;
}

void AzureKinectDevice::CaptureColorImage()
{
	int32 Width = 0, Height = 0;
	uint8* SourceBuffer;

	if (RemapMode == EKinectRemap::COLOR_TO_DEPTH)
	{
		k4a::image DepthCapture = Capture.get_depth_image();
		k4a::image ColorCapture = Capture.get_color_image();

		if (!DepthCapture.is_valid() || !ColorCapture.is_valid()) return;

		Width = DepthCapture.get_width_pixels();
		Height = DepthCapture.get_height_pixels();

		if (Width == 0 || Height == 0) return;

		//
		if (!RemapImage || !RemapImage.is_valid())
		{
			RemapImage = k4a::image::create(K4A_IMAGE_FORMAT_COLOR_BGRA32, Width, Height, Width * static_cast<int>(sizeof(uint8) * 4));
		}

		try
		{
			KinectTransformation.color_image_to_depth_camera(DepthCapture, ColorCapture, &RemapImage);
		}
		catch (const k4a::error& Err)
		{
			FString Msg(ANSI_TO_TCHAR(Err.what()));
			UE_LOG(AzureKinectDeviceLog, Error, TEXT("Cant't transform Color to Depth: %s"), *Msg);
			return;
		}

		SourceBuffer = RemapImage.get_buffer();

		DepthCapture.reset();
		ColorCapture.reset();
	}
	else
	{
		k4a::image ColorCapture = Capture.get_color_image();

		if (!ColorCapture.is_valid()) return;

		Width = ColorCapture.get_width_pixels();
		Height = ColorCapture.get_height_pixels();
		if (Width == 0 || Height == 0) return;

		SourceBuffer = ColorCapture.get_buffer();

		ColorCapture.reset();
	}

	if (ColorTexture->GetSurfaceWidth() != Width || ColorTexture->GetSurfaceHeight() != Height)
	{
		ColorTexture->InitCustomFormat(Width, Height, EPixelFormat::PF_B8G8R8A8, false);
		ColorTexture->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8;
		ColorTexture->UpdateResource();
	}
	else
	{

		FTextureResource* TextureResource = ColorTexture->Resource;
		auto Region = FUpdateTextureRegion2D(0, 0, 0, 0, Width, Height);

		ENQUEUE_RENDER_COMMAND(UpdateTextureData)(
			[TextureResource, Region, SourceBuffer](FRHICommandListImmediate& RHICmdList) {
				FTexture2DRHIRef Texture2D = TextureResource->TextureRHI ? TextureResource->TextureRHI->GetTexture2D() : nullptr;
				if (!Texture2D)
				{
					return;
				}
				RHIUpdateTexture2D(Texture2D, 0, Region, 4 * Region.Width, SourceBuffer);
			});
	}

}

void AzureKinectDevice::CaptureDepthImage()
{
	int32 Width = 0, Height = 0;
	uint8* SourceBuffer;
	if (RemapMode == EKinectRemap::DEPTH_TO_COLOR)
	{
		k4a::image DepthCapture = Capture.get_depth_image();
		k4a::image ColorCapture = Capture.get_color_image();

		if (!DepthCapture.is_valid() || !ColorCapture.is_valid()) return;

		Width = ColorCapture.get_width_pixels();
		Height = ColorCapture.get_height_pixels();

		if (Width == 0 || Height == 0) return;

		//
		if (!RemapImage || !RemapImage.is_valid())
		{
			RemapImage = k4a::image::create(K4A_IMAGE_FORMAT_DEPTH16, Width, Height, Width * static_cast<int>(sizeof(uint16)));
		}

		try
		{
			KinectTransformation.depth_image_to_color_camera(DepthCapture, &RemapImage);
		}
		catch (const k4a::error& Err)
		{
			FString Msg(ANSI_TO_TCHAR(Err.what()));
			UE_LOG(AzureKinectDeviceLog, Error, TEXT("Cant't transform Depth to Color: %s"), *Msg);
			return;
		}

		SourceBuffer = RemapImage.get_buffer();

		DepthCapture.reset();
		ColorCapture.reset();
	}
	else
	{
		k4a::image DepthCapture = Capture.get_depth_image();
		if (!DepthCapture.is_valid()) return;

		Width = DepthCapture.get_width_pixels();
		Height = DepthCapture.get_height_pixels();

		if (Width == 0 || Height == 0) return;

		SourceBuffer = DepthCapture.get_buffer();

		DepthCapture.reset();
	}

	if (DepthTexture->GetSurfaceWidth() != Width || DepthTexture->GetSurfaceHeight() != Height)
	{
		DepthTexture->InitCustomFormat(Width, Height, EPixelFormat::PF_R8G8B8A8, true);
		DepthTexture->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8;
		DepthTexture->UpdateResource();
	}
	else
	{
		/* 이미지 버퍼 채우기.
		* SourceBuffer = {R, G, R, G, R, G, ...}형태로 받고, R값만 존재. (SourceBuffer = DepthCapture.get_buffer();)
		* R = 카메라에서 가까울 수록 값이 큼.
		* G = 카메라에서 멀어질 수록 값이 작음. => 생각하는 Depth값일 가능성.
		* 
		* 
		* 
		*/

		TArray<uint8> SrcData;
		SrcData.Reset(Width * Height * 4);
		for (int hi = 0; hi < Height; hi++)
		{
			for (int wi = 0; wi < Width; wi++)
			{
				int index = hi * Width + wi;
				uint16 R = SourceBuffer[index * 2];
				uint16 G = SourceBuffer[index * 2 + 1];
				uint16 Sample = G << 8 | R; //미미한 G값을 증폭 하고 처리.

				SrcData.Push(SourceBuffer[index * 2]);
				SrcData.Push(SourceBuffer[index * 2 + 1]);
				SrcData.Push(Sample > 0 ? 0x00 : 0xFF);
				SrcData.Push(0xFF);

			}
		}

		FTextureResource* TextureResource = DepthTexture->Resource;
		auto Region = FUpdateTextureRegion2D(0, 0, 0, 0, Width, Height);

		ENQUEUE_RENDER_COMMAND(UpdateTextureData)(
			[TextureResource, Region, SrcData](FRHICommandListImmediate& RHICmdList) {
				FTexture2DRHIRef Texture2D = TextureResource->TextureRHI ? TextureResource->TextureRHI->GetTexture2D() : nullptr;
				if (!Texture2D)
				{
					return;
				}
				RHIUpdateTexture2D(Texture2D, 0, Region, 4 * Region.Width, SrcData.GetData());

			});
	}

}

void AzureKinectDevice::CaptureInflaredImage()
{
	const k4a::image& InflaredCapture = Capture.get_ir_image();
	if (!InflaredCapture.is_valid()) return;

	int32 Width = InflaredCapture.get_width_pixels(), Height = InflaredCapture.get_height_pixels();
	if (Width == 0 || Height == 0) return;

	if (InflaredTexture->GetSurfaceWidth() != Width || InflaredTexture->GetSurfaceWidth() != Height)
	{
		InflaredTexture->InitCustomFormat(Width, Height, EPixelFormat::PF_R8G8B8A8, true);
		InflaredTexture->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8;
		InflaredTexture->UpdateResource();
	}
	else
	{
		const uint8* S = InflaredCapture.get_buffer();
		TArray<uint8> SrcData;
		SrcData.Reset(Width * Height * 4);
		for (int hi = 0; hi < Height; hi++)
		{
			for (int wi = 0; wi < Width; wi++)
			{
				int index = hi * Width + wi;

				if (S[index * 2] + S[index * 2 + 1] > 0)
				{
					SrcData.Push(S[index * 2]);
					SrcData.Push(S[index * 2]);
					SrcData.Push(0x00);
					SrcData.Push(S[index * 2]);
				}
				else
				{
					SrcData.Push(0x00);
					SrcData.Push(0x00);
					SrcData.Push(0xff);
					SrcData.Push(0x00);
				}
			}
		}

		FTextureResource* TextureResource = InflaredTexture->Resource;
		auto Region = FUpdateTextureRegion2D(0, 0, 0, 0, Width, Height);

		ENQUEUE_RENDER_COMMAND(UpdateTextureData)(
			[TextureResource, Region, SrcData](FRHICommandListImmediate& RHICmdList) {
				FTexture2DRHIRef Texture2D = TextureResource->TextureRHI ? TextureResource->TextureRHI->GetTexture2D() : nullptr;
				if (!Texture2D)
				{
					return;
				}

				RHIUpdateTexture2D(Texture2D, 0, Region, 4 * Region.Width, SrcData.GetData());
			});
	}

}

void AzureKinectDevice::CaptureBodyIndexImage(const k4abt::frame& BodyFrame)
{
	k4a::image BodyIndexMap = BodyFrame.get_body_index_map();

	int32 Width = BodyIndexMap.get_width_pixels(), Height = BodyIndexMap.get_height_pixels();
	if (Width == 0 || Height == 0) return;

	if (BodyIndexTexture->GetSurfaceWidth() != Width || BodyIndexTexture->GetSurfaceHeight() != Height)
	{
		BodyIndexTexture->InitCustomFormat(Width, Height, EPixelFormat::PF_R8G8B8A8, true);
		BodyIndexTexture->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8;
		BodyIndexTexture->UpdateResource();
	}
	else
	{
		uint8* S = BodyIndexMap.get_buffer();
		TArray<uint8> SrcData;
		SrcData.Reset(Width * Height * 4);
		for (int i = 0; i < Width * Height; i++)
		{
			SrcData.Push(S[i] > 0 ? 0x00 : 0xff);
			SrcData.Push(S[i]);
			SrcData.Push(S[i]);
			SrcData.Push(S[i] > 0 ? 0x00 : 0xff);
		}

		FTextureResource* TextureResource = BodyIndexTexture->Resource;
		auto Region = FUpdateTextureRegion2D(0, 0, 0, 0, Width, Height);

		ENQUEUE_RENDER_COMMAND(UpdateTextureData)(
			[TextureResource, Region, SrcData](FRHICommandListImmediate& RHICmdList) {
				FTexture2DRHIRef Texture2D = TextureResource->TextureRHI ? TextureResource->TextureRHI->GetTexture2D() : nullptr;
				if (!Texture2D)
				{
					return;
				}
				RHIUpdateTexture2D(Texture2D, 0, Region, 4 * Region.Width, SrcData.GetData());

			});
	}

}
