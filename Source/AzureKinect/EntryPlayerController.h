// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widget/EntryWidget.h"
#include "EntryPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API AEntryPlayerController : public APlayerController
{
	GENERATED_BODY()

	AEntryPlayerController();
	virtual void BeginPlay() override;

public:
	TSubclassOf<UEntryWidget> EntryWidgetClass;
	UEntryWidget* EntryWidget;
};
