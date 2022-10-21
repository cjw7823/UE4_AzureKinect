// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainPlayerController.h"
#include "HAL/FileManagerGeneric.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "Components/CanvasPanel.h"
#include "Pictogram.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API UPictogram : public UUserWidget
{
	GENERATED_BODY()

public:
	UPictogram(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	void Init();
	void SpawnPictogram();

	UFUNCTION()
		void MovePictogram(UImage* image);

	void LoadFileToString(FString& Result, const TCHAR* Filename);

	static SelectLevel Level;
	static Select_Button Button;

	UPROPERTY()
		TArray<UTexture2D*> Low_pictogram1;
	UPROPERTY()
		TArray<UTexture2D*> Low_pictogram2;
	UPROPERTY()
		TArray<UTexture2D*> Low_pictogram3;
	UPROPERTY()
		TArray<UTexture2D*> Low_pictogram4;
	UPROPERTY()
		TArray<UTexture2D*> Low_pictogram5;

	UPROPERTY()
		TArray<UTexture2D*> Middle_pictogram1;
	UPROPERTY()
		TArray<UTexture2D*> Middle_pictogram2;
	UPROPERTY()
		TArray<UTexture2D*> Middle_pictogram3;
	UPROPERTY()
		TArray<UTexture2D*> Middle_pictogram4;
	UPROPERTY()
		TArray<UTexture2D*> Middle_pictogram5;
	
	UPROPERTY()
		TArray<UTexture2D*> High_pictogram1;
	UPROPERTY()
		TArray<UTexture2D*> High_pictogram2;
	UPROPERTY()
		TArray<UTexture2D*> High_pictogram3;
	UPROPERTY()
		TArray<UTexture2D*> High_pictogram4;
	UPROPERTY()
		TArray<UTexture2D*> High_pictogram5;

	UPROPERTY()
		TArray<double> Timing;

	UPROPERTY(BlueprintReadOnly)
		TArray<UTexture2D*> pictogram;

	UPROPERTY(BlueprintReadOnly)
		uint8 level;
	UPROPERTY(BlueprintReadOnly)
		uint8 button;

	UPROPERTY()
		UMediaPlayer* MediaPlayer;

	UPROPERTY(meta = (BindWidget))
		UCanvasPanel* CanvasPanel_0;
};
