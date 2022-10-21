// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "Components/AudioComponent.h"
#include "ServerWidget_2_2.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_2_2 : public UUserWidget
{
	GENERATED_BODY()

public:
	UServerWidget_2_2(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Background();

	UPROPERTY(BlueprintReadOnly, meta = (bindwidget))
		UListView* ListView_Hight;
	UPROPERTY(BlueprintReadOnly, meta = (bindwidget))
		UListView* ListView_Sex;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Sex;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Hight;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Sex_Toggle;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Hight_Toggle;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Sex_Back;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Hight_Back;
	UPROPERTY(meta = (bindwidget))
		UImage* S_bar;

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
		AActor* User_Doll;

	UPROPERTY()
		USoundWave* Back_04;

	UPROPERTY()
		UAudioComponent* Audio01;

	UPROPERTY()
		AActor* BGM;
};
