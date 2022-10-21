// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "CustomEnum.h"
#include "Components/AudioComponent.h"
#include "ServerWidget_3_3.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_3_3 : public UUserWidget
{
	GENERATED_BODY()

public:
	UServerWidget_3_3(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();
	void SetContents();

	static SelectLevel Level;
	static Select_Button Button;

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
		UTextBlock* TextBlock_Name;
	UPROPERTY(meta = (bindwidget))
		UTextBlock* TextBlock_Explanation;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Explanation;

	UPROPERTY()
		TArray<UTexture2D*> TitleTextures;
	UPROPERTY()
		TArray<UTexture2D*> Explanation;

	UPROPERTY()
		AActor* GuideGirl;

	UPROPERTY()
		USoundWave* Back_01;

	UPROPERTY()
		AActor* Audio01;
};
