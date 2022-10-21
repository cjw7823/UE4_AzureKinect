// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "Components/TextBlock.h"
#include "CustomEnum.h"
#include "Components/AudioComponent.h"
#include "ServerWidget_3_2.generated.h"

/**
 * 
 */ 
UCLASS()
class AZUREKINECT_API UServerWidget_3_2 : public UUserWidget
{
	GENERATED_BODY()
public:
	UServerWidget_3_2(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Title;
	UPROPERTY()
		UTexture2D* LowTitle;
	UPROPERTY()
		UTexture2D* MiddleTitle;
	UPROPERTY()
		UTexture2D* HighTitle;

	UPROPERTY()
		AActor* GuideGirl;

	UPROPERTY()
		USoundWave* Back_01;

	UPROPERTY()
		UAudioComponent* Audio01;
};
