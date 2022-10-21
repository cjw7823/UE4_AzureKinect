// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ServerWidget_4_2.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_4_2 : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UServerWidget_4_2(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	FTimerHandle timerhandle;

	UFUNCTION()
		void CountDown();

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	UPROPERTY()
		AActor* GuideGirl;
	UPROPERTY()
		AMainPlayerController* ClientMainPC;
};