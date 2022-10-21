// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/AudioComponent.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "ImgMediaSource.h"
#include "ServerWidget_1_1.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_1_1 : public UUserWidget
{
	GENERATED_BODY()
public:
	UServerWidget_1_1(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	UFUNCTION()
		void OnPlaybackResumed();
	UFUNCTION()
		void EndPlay();

	UFUNCTION()
		void OpenDoor();
	UFUNCTION()
		void Dissolve();

	UPROPERTY(meta = (bindwidget))
		UImage* Image_main;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_main2;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UImgMediaSource* MediaSource;

	UPROPERTY()
		USoundWave* Back_02;
	UPROPERTY()
		USoundWave* Transition_04;

	UPROPERTY()
		UAudioComponent* Audio01;
	UPROPERTY()
		UAudioComponent* Audio02;
	UPROPERTY()
		AActor* BGM;

	FTimerHandle timerhandle;
};
