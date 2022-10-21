// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ClientWidget_2_3.generated.h"

class AMainPlayerController;
class UClientWidget_3_1;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_2_3 : public UUserWidget
{
	GENERATED_BODY()

public:
	UClientWidget_2_3(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetMediaPath_Background();

	UFUNCTION()
		void OnClick_Button_Userdata();
	UFUNCTION()
		void OnClick_Button_Enter();
	UFUNCTION()
		void OnClick_Button_Helper();
	UFUNCTION()
		void OnPressed_Button_Userdata();
	UFUNCTION()
		void OnPressed_Button_Enter();
	UFUNCTION()
		void OnReleased_Button();

	UPROPERTY(meta = (bindwidget))
		UButton* Button_Userdata;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Enter;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Helper;

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
		USoundWave* Button_14;
	UPROPERTY()
		USoundWave* Button_09;

	int32 InitTimer;
	UFUNCTION()
		void CheckInitTimer();
	FTimerHandle InitTimerhandle;
};
