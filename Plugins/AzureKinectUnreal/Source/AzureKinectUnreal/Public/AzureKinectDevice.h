// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "k4a/k4a.hpp"
#include "k4abt.hpp"
#include "AzureKinectThread.h"
#include "AzureKinectBody.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Delegates/IDelegateInstance.h"

DECLARE_LOG_CATEGORY_EXTERN(AzureKinectDeviceLog, Log, All);

/**
 * A representation of the Native Azure Kinect Device that is used to call the
 * connected device's (K4A & K4ABT) API for starting & stopping camera sensors,
 * creating & destroying the body tracker, capturing the body frame etc.
 */
class AZUREKINECTUNREAL_API AzureKinectDevice
{
public:
	/** Ctor */
	AzureKinectDevice();
	/** Ctor that initializes this azure kinect device with the id and timeout params. */
	AzureKinectDevice(int32 DeviceId, int32 TimeOut, EKinectRemap remap);
	/** Destructor */
	~AzureKinectDevice();

	/** Initalizes the Azure kinect device with the given Depth Mode. */
	bool Initialize(k4a_depth_mode_t DepthMode, k4a_color_resolution_t ColorMode);
	/** Shuts down this device */
	void Shutdown();

	/**
	 * Captures the device body tracking frame, enqueues the capture, pops the tracker body frame result
	 * and releases the body frame. 
	 * 
	 * @note This is run on a different thread to improve performance.
	 */
	void CaptureBodyTrackingFrame();

	/** The timeout for the API calls in milliseconds. */
	int32 GetTimeOutInMilliSecs() const;

	/** Returns an array of the tracked bodies by this device. */
	TArray<UAzureKinectBody*> GetBodies() const;

	/** Whether this device is initialized or not. */
	bool IsInitialized() const;

	void ToggleShowLogsAndOnScreenMsgs(bool ShouldShowLogs, bool ShouldShowOnScreenMsgs);

	UTextureRenderTarget2D* DepthTexture;
	UTextureRenderTarget2D* ColorTexture;
	UTextureRenderTarget2D* InflaredTexture;
	UTextureRenderTarget2D* BodyIndexTexture;
	UTextureRenderTarget2D* MKVTexture;
	k4a_device_configuration_t deviceConfig;
	bool DoSaving;

	EKinectRemap RemapMode;

	k4a::capture Capture;
	k4a::image NativeDevice;
	k4a::transformation KinectTransformation;
	k4a::image RemapImage;




	//--------------------------------------
public:
	void Start2Save();
	void End2Save();
	void SaveToColorVideo();
	uint64_t Start2Load();
	void End2Load();
	void LoadToColorVideo(float time = -1.0f);

private:
	void CaptureColorImage();
	void CaptureDepthImage();
	void CaptureInflaredImage();
	void CaptureBodyIndexImage(const k4abt::frame& BodyFrame);

	/** A handle to the native k4a device that is used in starting and stopping camera sensors. */
	k4a::device NativeKinectDevice;
	/** The Id of this device. Default is 0. */
	int32 DeviceId;
	/** A handle to the native k4abt body tracker that is used to get the body frame and the skeleton joints data. */
	k4abt::tracker NativeBodyTracker;
	/** The timeout for the API calls. Default is 0, which means it is non-blocking. */
	int32 TimeOutInMilliSecs;
	/** TimeOutInMilliSecs converted to std::chrono::milliseconds */
	std::chrono::milliseconds TimeOutInMilliSecsConverted;

	/** A pointer to the thread that does the body capturing. */
	FAzureKinectThread *Thread;

	/** Whether this device is initialized or not. */
	bool bIsInitialized;

	/** 
	 * An array of bodies that are tracked by this device. 
	 * The bodies in the array are automatically updated with new kinect body joint data.
	 */
	TArray<UAzureKinectBody*> Bodies;

	/** The frequency with which the ticker delegate is called. Set to 16 ms = 60 fps. */
	const float TickInterval = 0.016666666f;

	/** A delegate handle to start and stop polling. */
	FDelegateHandle TickHandle;

	/** Initializes the Bodies TArray with correct length/size and default values. */
	void InitializeBodies();

	/** Initializes the kinect thread. */
	void StartKinectThread();

	/**
	 * The polling function that is called by the ticker delegate.
	 * This updates the UAzureKinectBody in Bodies array with the data
	 * from the Kinect Body.
	 */
	bool OnTick(float DeltaTime);

	/** For debugging only */
	bool bShowAllLogs;
	bool bShowOnScreenMsgs;
};
