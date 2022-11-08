// Fill out your copyright notice in the Description page of Project Settings.


#include "AzureKinectManager.h"

DEFINE_LOG_CATEGORY(AzureKinectLog);

UAzureKinectManager *UAzureKinectManager::Instance = nullptr;

UAzureKinectManager::UAzureKinectManager()
{
}

UAzureKinectManager::~UAzureKinectManager()
{
	ShutdownAllDevices();

	RemoveFromRoot();
	Instance = nullptr;
}

void UAzureKinectManager::InitDevice(int32 DeviceId, EKinectDepthMode DepthMode, EKinectColorResolution ColorMode, EKinectRemap remap, int32 TimeOutInMilliSecs)
{
	if (!Instance)
	{
		Instance = NewObject<UAzureKinectManager>();
		if (!Instance)
		{
			UE_LOG(AzureKinectLog, Error, TEXT("Could not create an instance for UAzureKinectManager"));
			return;
		}

		Instance->AddToRoot();
	}

	if (Instance->KinectDevicesById.Contains(DeviceId))
	{
		UE_LOG(AzureKinectLog, Error, TEXT("Kinect device (id : %d) already initialized"), DeviceId);
		return;
	}

	AzureKinectDevice *KinectDevice = new AzureKinectDevice(DeviceId, TimeOutInMilliSecs, remap);
	bool bIsInitialized = KinectDevice->Initialize((k4a_depth_mode_t)DepthMode, (k4a_color_resolution_t)ColorMode);

	if (bIsInitialized)
	{
		Instance->KinectDevicesById.Add(DeviceId, KinectDevice);
		UE_LOG(AzureKinectLog, Warning, TEXT("Kinect device (id : %d) added to TMap : Count : %d"), DeviceId, Instance->KinectDevicesById.Num());
	}
	else
	{
		UE_LOG(AzureKinectLog, Error, TEXT("Kinect device (id : %d) initialization Failed, so cleaning up."), DeviceId);
		KinectDevice->Shutdown();
	}
}

void UAzureKinectManager::ShutdownDevice(int32 DeviceId)
{
	if (!Instance)
	{
		UE_LOG(AzureKinectLog, Error, TEXT("UAzureKinectManager Instance is nullptr"));
		return;
	}

	AzureKinectDevice **Device = Instance->KinectDevicesById.Find(DeviceId);
	if (!Device || !(*Device))
	{
		UE_LOG(AzureKinectLog, Error, TEXT("Kinect device (id : %d) was not initialized to be shutdown"), DeviceId);
		return;
	}

	(*Device)->Shutdown();
	Instance->KinectDevicesById.Remove(DeviceId);
	UE_LOG(AzureKinectLog, Warning, TEXT("Kinect device (id : %d) was shutdown. TMap count : %d"), DeviceId, Instance->KinectDevicesById.Num());
}

bool UAzureKinectManager::IsDeviceInitialized(int32 DeviceId)
{
	AzureKinectDevice *Device = GetDevice(DeviceId);
	if (!Device)
	{
		return false;
	}

	return Device->IsInitialized();
}

void UAzureKinectManager::ShutdownAllDevices()
{
	for (TPair<int32, AzureKinectDevice*> kvp : KinectDevicesById)
	{
		if (kvp.Value)
		{
			kvp.Value->Shutdown();
		}
	}

	KinectDevicesById.Empty();
}

AzureKinectDevice *UAzureKinectManager::GetDevice(int32 DeviceId)
{
	if (!Instance)
	{
		UE_LOG(AzureKinectLog, Error, TEXT("UAzureKinectManager Instance is nullptr"));
		return nullptr;
	}

	AzureKinectDevice **Device = Instance->KinectDevicesById.Find(DeviceId);
	if (!Device || !(*Device))
	{
		UE_LOG(AzureKinectLog, Error, TEXT("Kinect device (id : %d) was not found"), DeviceId);
		return nullptr;
	}

	return (*Device);
}

TArray<UAzureKinectBody*> UAzureKinectManager::GetBodies(int32 DeviceId)
{
	AzureKinectDevice *Device = GetDevice(DeviceId);
	if (!Device)
	{
		UE_LOG(AzureKinectLog, Warning, TEXT("Returning empty TArray of UAzureKinectBody"));
		return TArray<UAzureKinectBody*>();
	}

	return Device->GetBodies();
}

int32 UAzureKinectManager::GetJointCount()
{
	return static_cast<int32>(JointCount);
}

void UAzureKinectManager::ToggleDeviceLogging(int32 DeviceId, bool ShouldShowLogs, bool ShouldShowOnScreenMsgs)
{
	AzureKinectDevice *Device = GetDevice(DeviceId);
	if (Device)
	{
		Device->ToggleShowLogsAndOnScreenMsgs(ShouldShowLogs, ShouldShowOnScreenMsgs);
	}
}

void UAzureKinectManager::SetColorTexture(UTextureRenderTarget2D* texture)
{
	Instance->KinectDevicesById.FindRef(0)->ColorTexture = texture;
}

void UAzureKinectManager::SetDepthTexture(UTextureRenderTarget2D* texture)
{
	Instance->KinectDevicesById.FindRef(0)->DepthTexture = texture;
}

void UAzureKinectManager::SetInflaredTexture(UTextureRenderTarget2D* texture)
{
	Instance->KinectDevicesById.FindRef(0)->InflaredTexture = texture;
}

void UAzureKinectManager::SetBodyIndexTexture(UTextureRenderTarget2D* texture)
{
	Instance->KinectDevicesById.FindRef(0)->BodyIndexTexture = texture;
}

void UAzureKinectManager::start_to_save()
{
	Instance->KinectDevicesById.FindRef(0)->Start2Save();
}

void UAzureKinectManager::end_to_save()
{
	Instance->KinectDevicesById.FindRef(0)->End2Save();
}

int64 UAzureKinectManager::start_to_load(UTextureRenderTarget2D* texture)
{
	uint64_t duration = 0;
	duration = Instance->KinectDevicesById.FindRef(0)->Start2Load(); // playback opne
	Instance->KinectDevicesById.FindRef(0)->MKVTexture = texture; // capture in playback

	return duration;
}

void UAzureKinectManager::end_to_load()
{
	Instance->KinectDevicesById.FindRef(0)->MKVTexture = nullptr;
	Instance->KinectDevicesById.FindRef(0)->End2Load();
}

void UAzureKinectManager::play_color_video(float time)
{
	Instance->KinectDevicesById.FindRef(0)->LoadToColorVideo(time);
}
