// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "Components/TextBlock.h"
#include "ClientWidget_4_3.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_4_3 : public UUserWidget
{
	GENERATED_BODY()
public:
	UClientWidget_4_3(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	FTimerHandle timerhandle;

	UFUNCTION()
		void CountDown();
	UFUNCTION()
		void OnClick_Button_Helper();
	UFUNCTION()
		void OnClick_Button_Back();
	UFUNCTION()
		void OnClick_Button_Retry();
	UFUNCTION()
		void OnClick_Button_Next();

	UPROPERTY(meta = (bindwidget))
		UImage* Image_CountdownText;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Helper;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Back;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Retry;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Next;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	UPROPERTY()
		AMainPlayerController* MainPC;

	UPROPERTY()
		USoundWave* Button_11;
	UPROPERTY()
		USoundWave* Button_09;
};
