// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ClientWidget_5_2.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_5_2 : public UUserWidget
{
	GENERATED_BODY()
public:
	UClientWidget_5_2(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetPlayButtonTexture(UTexture2D* texture, UTexture2D* texture_toggle);
	void SetMediaPath_Background();

	UFUNCTION()
		void OnClick_Button_Back();
	UFUNCTION()
		void OnClick_Button_Slow();
	UFUNCTION()
		void OnClick_Button_Play();
	UFUNCTION()
		void OnClick_Button_Fast();
	UFUNCTION()
		void Test();
	UFUNCTION()
		void OnMouseCaptureBegin();
	UFUNCTION()
		void OnMouseCaptureEnd();

	UPROPERTY(meta = (bindwidget))
		UButton* Button_Slow;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Play;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Fast;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Back;
	UPROPERTY(meta = (bindwidget))
		USlider* Seeker;

	UPROPERTY()
		UTexture2D* Texture_play;
	UPROPERTY()
		UTexture2D* Texture_pause;
	UPROPERTY()
		UTexture2D* Texture_playToggle;
	UPROPERTY()
		UTexture2D* Texture_pauseToggle;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	bool is_play;
	
	UPROPERTY()
		AMainPlayerController* MainPC;

	UPROPERTY()
		USoundWave* Button_14;
	UPROPERTY()
		USoundWave* Button_09;

	int32 InitTimer;
	UFUNCTION()
		void CheckInitTimer();
	FTimerHandle InitTimerhandle;
};
