// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "Components/AudioComponent.h"
#include "ServerWidget_2_1.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_2_1 : public UUserWidget
{
	GENERATED_BODY()

public:
	UServerWidget_2_1(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetMediaPath_Background(FString B_path);
	void SetMediaPath_Video(FString video_path);
	void SetTextGuide(int32 index);
	void SetZOrder(int32 index);

	UFUNCTION()
		void FirstZOrder();

	bool loading;
	int32 MaxPathIndex;
	int32 CurPathIndex;
	TArray<FString> VideoPathes;
	TArray<UTexture2D*> TextGuide;
	TArray<UTexture2D*> TextGuideNum;

	TArray<UImage*> ImageVideos;
	TArray<UMediaPlayer*> MediaPlayers;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Video;
	UPROPERTY()
		UMediaTexture* MediaTexture_Video;
	UPROPERTY()
		UMediaPlayer* MediaPlayer_Video;
	UPROPERTY()
		UFileMediaSource* FileMediaSource_Video;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Video2;
	UPROPERTY()
		UMediaTexture* MediaTexture_Video2;
	UPROPERTY()
		UMediaPlayer* MediaPlayer_Video2;
	UPROPERTY()
		UFileMediaSource* FileMediaSource_Video2;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Video3;
	UPROPERTY()
		UMediaTexture* MediaTexture_Video3;
	UPROPERTY()
		UMediaPlayer* MediaPlayer_Video3;
	UPROPERTY()
		UFileMediaSource* FileMediaSource_Video3;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Video4;
	UPROPERTY()
		UMediaTexture* MediaTexture_Video4;
	UPROPERTY()
		UMediaPlayer* MediaPlayer_Video4;
	UPROPERTY()
		UFileMediaSource* FileMediaSource_Video4;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Video5;
	UPROPERTY()
		UMediaTexture* MediaTexture_Video5;
	UPROPERTY()
		UMediaPlayer* MediaPlayer_Video5;
	UPROPERTY()
		UFileMediaSource* FileMediaSource_Video5;


	UPROPERTY(meta = (bindwidget))
		UImage* Image_Guide;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_GuideNum;

	UPROPERTY()
		USoundWave* Back_04;

	UPROPERTY()
		UAudioComponent* Audio04;
	UPROPERTY()
		AActor* GuideGirl;
	UPROPERTY()
		AActor* BGM;
};
