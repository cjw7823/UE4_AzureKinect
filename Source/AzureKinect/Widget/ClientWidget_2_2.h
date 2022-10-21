// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "ClientWidget_2_2.generated.h"

class AMainPlayerController;
class UClientWidget_2_3;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_2_2 : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UClientWidget_2_2(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void Hight_Click(UObject* obj);
	void Sex_Click(UObject* obj);
	void Sync_ListView(float a, float b);
	void SetMediaPath_Background();

	UFUNCTION()
		void OnClick_Button_Next();
	UFUNCTION()
		void OnPressed_Button_Sex();
	UFUNCTION()
		void OnPressed_Button_Hight();
	UFUNCTION()
		void OnReleased_Button();

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	UPROPERTY(BlueprintReadOnly, meta = (bindwidget))
		UListView* ListView_Hight;
	UPROPERTY(BlueprintReadOnly, meta = (bindwidget))
		UListView* ListView_Sex;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Finish;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Sex;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Hight;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Sex;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Hight;
	UPROPERTY(meta = (bindwidget))
		UImage* bar;

	bool Finish_Input_Hight;
	bool Finish_Input_Sex;

	UPROPERTY()
		AMainPlayerController* MainPC;
	UPROPERTY()
		UClientWidget_2_3* ClientWidget_2_3;

	UPROPERTY()
		USoundWave* Button_14;
	UPROPERTY()
		USoundWave* Button_04;
	UPROPERTY()
		USoundWave* Button_10;

	int32 InitTimer;
	UFUNCTION()
		void CheckInitTimer();
	FTimerHandle InitTimerhandle;
};
