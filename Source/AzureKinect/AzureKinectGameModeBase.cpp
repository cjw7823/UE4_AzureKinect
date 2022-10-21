// Fill out your copyright notice in the Description page of Project Settings.


#include "AzureKinectGameModeBase.h"
#include "EntryPlayerController.h"

AAzureKinectGameModeBase::AAzureKinectGameModeBase()
{
	PlayerControllerClass = AEntryPlayerController::StaticClass();
}
