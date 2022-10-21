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
#include "CustomEnum.h"
#include "ClientWidget_3_2.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_3_2 : public UUserWidget
{
	GENERATED_BODY()
public:
	UClientWidget_3_2(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	static SelectLevel Level;

	UPROPERTY()
		TArray<UTexture2D*> ButtonTextures;
	UPROPERTY()
		TArray<UTexture2D*> ButtonTextures_Toggle;

	UFUNCTION()
		void SetButtonTexture();

	UFUNCTION()
		void OnClick_Button_1();
	UFUNCTION()
		void OnClick_Button_2();
	UFUNCTION()
		void OnClick_Button_3();
	UFUNCTION()
		void OnClick_Button_4();
	UFUNCTION()
		void OnClick_Button_5();
	UFUNCTION()
		void OnClick_Button_Helper();
	UFUNCTION()
		void OnClick_Button_Back();

	UPROPERTY(meta = (bindwidget))
		UButton* Button_1;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_2;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_3;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_4;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_5;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Helper;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Back;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Level;

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
