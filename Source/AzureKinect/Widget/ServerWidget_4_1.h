// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ImgMediaSource.h"
#include "Components/TextBlock.h"
#include "Components/AudioComponent.h"
#include "ServerWidget_4_1.generated.h"

class UMainGameInstance;
class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_4_1 : public UUserWidget
{
	GENERATED_BODY()
public:
	UServerWidget_4_1(const FObjectInitializer& ObjectInitializer);
	

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void SetMediaPath_Sequence();

	UFUNCTION()
		void CheckSkeleton();
	UFUNCTION()
		void PlaySequence();
	UFUNCTION()
		void ShowSequence();
	UFUNCTION()
		FText Textbinding();

	UPROPERTY(BlueprintReadWrite)
		int32 Percent;

	float time;
	FTimerHandle timerhandle;
	bool warning;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Sequence;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UImgMediaSource* MediaSource;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_User;
	UPROPERTY(meta = (bindwidget))
		UTextBlock* TextBlock_Per;
	UPROPERTY()
		UMaterial* User_Material;

	UPROPERTY()
		UMainGameInstance* MainGM;
	UPROPERTY()
		AMainPlayerController* ClientMainPC;

	UPROPERTY()
		USoundWave* Back_06;
	UPROPERTY()
		USoundWave* Warning_03;

	UPROPERTY()
		UAudioComponent* Audio01;

	UPROPERTY()
		AActor* UserDoll;

	UPROPERTY()
		USkeletalMeshComponent* Skel;
};
