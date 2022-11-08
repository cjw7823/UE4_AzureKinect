// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ServerWidget_5_2.generated.h"

class AMainPlayerController;
class AReplay_Mannequin;
class Referee;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_5_2 : public UUserWidget
{
	GENERATED_BODY()

public:
	UServerWidget_5_2(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;
	void SetCoachingVideo();
	void SetUserVideo();
	void SetMediaPath_Background();

	UFUNCTION()
		void CheckOpenResource(FString OpenedUrl);
	UFUNCTION()
		void FailOpenResource(FString OpenedUrl);
	UFUNCTION()
		void EndPlay();
	UFUNCTION()
		void PlaybackSuspended();
	UFUNCTION()
		void OnPlaybackResumed();
	UFUNCTION()
		void SyncMediaDuration(float value);
	UFUNCTION()
		void SetSkeletalTransform(float InDeltaTime);
	UFUNCTION()
		void SetSkeletalTransform_FirstPose();

	bool is_OpenResource;
	double Duration;
	double CurPerDu;
	bool is_Play;
	Referee* referee;
	TArray<int32> CorrectFrame;

	TArray<FRotator> preRotation;

	UPROPERTY()
		UMaterial* User_Material;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Coaching;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_User;
	UPROPERTY(meta = (bindwidget))
		UTextBlock* TextBlock_Rate;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture_Background;
	UPROPERTY()
		UMediaPlayer* MediaPlayer_Background;
	UPROPERTY()
		UFileMediaSource* FileMediaSource_Background;

	UPROPERTY()
		AMainPlayerController* MainPC;
	UPROPERTY()
		AMainPlayerController* ClientMainPC;
	UPROPERTY()
		AReplay_Mannequin* ReplayMannequin;

public:
	FString FilePath;
	FString Json_String;
	TSharedPtr<FJsonObject> jsonObj;
	int32 FrameNum;

	UPROPERTY()
		AActor* GuideGirl;

	UPROPERTY(BlueprintReadWrite)
		float Delta_Time;

	UPROPERTY(BlueprintReadWrite)
		bool is_play_bp;
};
