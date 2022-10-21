// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AzureKinect.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMainGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

	UPROPERTY(BlueprintReadOnly)
		int User_Hight;
	UPROPERTY(BlueprintReadOnly)
		FString User_Sex;
	UPROPERTY(BlueprintReadWrite)
		uint8 TrackedSkeleton_Num;

	UPROPERTY()
	TArray<FString> Low_MediaPath;
	UPROPERTY()
	TArray<FString> Middle_MediaPath;
	UPROPERTY()
	TArray<FString> High_MediaPath;

	UPROPERTY()
		TArray<FString> Low_MediaPath_Side;
	UPROPERTY()
		TArray<FString> Middle_MediaPath_Side;
	UPROPERTY()
		TArray<FString> High_MediaPath_Side;
};
