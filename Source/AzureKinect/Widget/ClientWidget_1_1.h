// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
//#include "FileMediaSource.h"
#include "ImgMediaSource.h"
#include "ClientWidget_1_1.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_1_1 : public UUserWidget
{
	GENERATED_BODY()
	
public:
	static bool isFirst;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	UFUNCTION()
		void OnPlaybackResumed();
	UFUNCTION()
		void EndPlay();

	UFUNCTION()
		void MouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UImgMediaSource* MediaSource;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_touch;

	UPROPERTY()
		AMainPlayerController* MainPC;
};
