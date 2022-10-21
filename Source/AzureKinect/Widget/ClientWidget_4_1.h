// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ClientWidget_4_1.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_4_1 : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	float LimitTime;
	bool SpawnWidget;

	UFUNCTION()
		void OnClick_Button_Helper();
	UFUNCTION()
		void OnClick_Button_Skip();

	UPROPERTY(meta = (bindwidget))
		UButton* Button_Helper;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Skip;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	AMainPlayerController* MainPC;
};
