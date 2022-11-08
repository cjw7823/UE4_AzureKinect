// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "CustomEnum.h"
#include "ClientWidget_3_3.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_3_3 : public UUserWidget
{
	GENERATED_BODY()

public:
	UClientWidget_3_3(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	static SelectLevel Level;
	static Select_Button Button;

	UFUNCTION()
		void OnClick_Button_Helper();
	UFUNCTION()
		void OnClick_Button_Back();
	UFUNCTION()
		void OnClick_Button_Next();

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
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Helper;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Back;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Next;

	UPROPERTY()
		UTexture2D* TitleTexture;
	
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
