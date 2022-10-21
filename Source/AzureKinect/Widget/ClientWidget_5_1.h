// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ImgMediaSource.h"
#include "ClientWidget_5_1.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_5_1 : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UClientWidget_5_1(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetMediaPath_Background();
	void SetMediaPath_RollingNumber();

	UFUNCTION()
		void OnPlaybackResumed();
	UFUNCTION()
		void EndPlay();

	UFUNCTION()
		void OnClick_Button_Helper();
	UFUNCTION()
		void OnClick_Button_Retry();
	UFUNCTION()
		void OnClick_Button_DetailCoaching();
	UFUNCTION()
		void OnClick_Button_NextLevel();
	UFUNCTION()
		void SetScoreText();

	FTimerHandle timerhandle;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_lastcut;
	
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Helper;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Retry;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_DetailCoaching;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_NextLevel;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	UPROPERTY(meta = (bindwidget), BlueprintReadWrite)
		UImage* Image_Rolling;
	UPROPERTY()
		UMediaTexture* MediaTexture_Rolling;
	UPROPERTY()
		UMediaPlayer* MediaPlayer_Rolling;
	UPROPERTY()
		UImgMediaSource* MediaSource_Rolling;

	UPROPERTY(meta = (bindwidget))
		UTextBlock* TextBlock_Score;

	UPROPERTY()
		AMainPlayerController* MainPC;

	UPROPERTY()
		USoundWave* Button_11;
	UPROPERTY()
		USoundWave* Button_09;

	int32 InitTimer;
	UFUNCTION()
		void CheckInitTimer();
	FTimerHandle InitTimerhandle;
};
