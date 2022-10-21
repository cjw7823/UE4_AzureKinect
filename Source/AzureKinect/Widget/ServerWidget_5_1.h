// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ImgMediaSource.h"
#include "ServerWidget_5_1.generated.h"

class Referee;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_5_1 : public UUserWidget
{
	GENERATED_BODY()
public:
	UServerWidget_5_1(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();
	void SetMediaPath_RollingNumber();

	void Scoring();

	UFUNCTION()
		void OnPlaybackResumed();
	UFUNCTION()
		void EndPlay();

	UFUNCTION()
		void SetTotalScore();
	
	Referee* referee;

	int32 TotalScore;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_lastcut;

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
		AActor* GuideGirl;

	UPROPERTY()
		USoundWave* ScoreBoard_02;
};
