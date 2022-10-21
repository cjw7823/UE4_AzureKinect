// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "Components/AudioComponent.h"
#include "ServerWidget_2_3.generated.h"

class UGuideGirlAnimInstance;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_2_3 : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UServerWidget_2_3(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	UFUNCTION()
		void CountDown();

	FTimerHandle timerhandle;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Userdata;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Enter;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Userdata_Toggle;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Enter_Toggle;

	UPROPERTY()
		AActor* GuideGirl;

	UPROPERTY()
		USoundWave* Back_01;

	UPROPERTY()
		UAudioComponent* Audio01;

	UPROPERTY()
		UGuideGirlAnimInstance* GuideAnim;
};
