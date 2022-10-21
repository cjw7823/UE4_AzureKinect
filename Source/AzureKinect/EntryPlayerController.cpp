// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryPlayerController.h"


AEntryPlayerController::AEntryPlayerController()
{
	ConstructorHelpers::FClassFinder<UEntryWidget> StartWidgetClass(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/EntryWidget.EntryWidget_C'"));

	if (StartWidgetClass.Succeeded())
	{
		EntryWidgetClass = StartWidgetClass.Class;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Blue, FString(TEXT("StartWidgetClass.Failed")));
	}
}

void AEntryPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(EntryWidgetClass))
	{
		EntryWidget = CreateWidget<UEntryWidget>(this, EntryWidgetClass);

		if (IsValid(EntryWidget))
		{
			//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Blue, "EntryWidget");
			EntryWidget->AddToViewport();
			SetShowMouseCursor(true);
			SetInputMode(FInputModeUIOnly());
		}
	}

}