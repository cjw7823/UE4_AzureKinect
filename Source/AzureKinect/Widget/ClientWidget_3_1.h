// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ClientWidget_3_1.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_3_1 : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UClientWidget_3_1(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	UFUNCTION()
		void OnClick_Button_LowLevel();
	UFUNCTION()
		void OnClick_Button_MiddleLevel();
	UFUNCTION()
		void OnClick_Button_HighLevel();
	UFUNCTION()
		void OnClick_Button_Helper();
	UFUNCTION()
		void OnClick_Button_Back();

	UFUNCTION()
		void OnPressed_Button_LowLevel();
	UFUNCTION()
		void OnPressed_Button_MiddleLevel();
	UFUNCTION()
		void OnPressed_Button_HighLevel();
	UFUNCTION()
		void OnReleased_Button();

	UPROPERTY(meta = (bindwidget))
		UButton* Button_LowLevel;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_MiddleLevel;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_HighLevel;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Helper;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Back;

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

	int32 InitTimer;
	UFUNCTION()
		void CheckInitTimer();
	FTimerHandle InitTimerhandle;
};
