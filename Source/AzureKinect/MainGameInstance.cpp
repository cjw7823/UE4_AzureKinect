// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "Kismet/KismetStringLibrary.h"

UMainGameInstance::UMainGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMainGameInstance::Init()
{
	Super::Init();

	Low_MediaPath.Add(FString(TEXT("./Movies/Low/1.mp4")));
	Low_MediaPath.Add(FString(TEXT("./Movies/Low/2.mp4")));
	Low_MediaPath.Add(FString(TEXT("./Movies/Low/3.mp4")));
	Low_MediaPath.Add(FString(TEXT("./Movies/Low/4.mp4")));
	Low_MediaPath.Add(FString(TEXT("./Movies/Low/5.mp4")));

	Middle_MediaPath.Add(FString(TEXT("./Movies/Middle/1.mp4")));
	Middle_MediaPath.Add(FString(TEXT("./Movies/Middle/2.mp4")));
	Middle_MediaPath.Add(FString(TEXT("./Movies/Middle/3.mp4")));
	Middle_MediaPath.Add(FString(TEXT("./Movies/Middle/4.mp4")));
	Middle_MediaPath.Add(FString(TEXT("./Movies/Middle/5.mp4")));

	High_MediaPath.Add(FString(TEXT("./Movies/High/1.mp4")));
	High_MediaPath.Add(FString(TEXT("./Movies/High/2.mp4")));
	High_MediaPath.Add(FString(TEXT("./Movies/High/3.mp4")));
	High_MediaPath.Add(FString(TEXT("./Movies/High/4.mp4")));
	High_MediaPath.Add(FString(TEXT("./Movies/High/5.mp4")));

	/*--------------------------------------------------------------------------------------*/

	Low_MediaPath_Side.Add(FString(TEXT("./Movies/Low/1s.mp4")));
	Low_MediaPath_Side.Add(FString(TEXT("./Movies/Low/2s.mp4")));
	Low_MediaPath_Side.Add(FString(TEXT("./Movies/Low/3s.mp4")));
	Low_MediaPath_Side.Add(FString(TEXT("./Movies/Low/4s.mp4")));
	Low_MediaPath_Side.Add(FString(TEXT("./Movies/Low/5s.mp4")));

	Middle_MediaPath_Side.Add(FString(TEXT("./Movies/Middle/1s.mp4")));
	Middle_MediaPath_Side.Add(FString(TEXT("./Movies/Middle/2s.mp4")));
	Middle_MediaPath_Side.Add(FString(TEXT("./Movies/Middle/3s.mp4")));
	Middle_MediaPath_Side.Add(FString(TEXT("./Movies/Middle/4s.mp4")));
	Middle_MediaPath_Side.Add(FString(TEXT("./Movies/Middle/5s.mp4")));

	High_MediaPath_Side.Add(FString(TEXT("./Movies/High/1s.mp4")));
	High_MediaPath_Side.Add(FString(TEXT("./Movies/High/2s.mp4")));
	High_MediaPath_Side.Add(FString(TEXT("./Movies/High/3s.mp4")));
	High_MediaPath_Side.Add(FString(TEXT("./Movies/High/4s.mp4")));
	High_MediaPath_Side.Add(FString(TEXT("./Movies/High/5s.mp4")));
}

void UMainGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UMainGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}