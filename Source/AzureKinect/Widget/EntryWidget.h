// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "Components/CircularThrobber.h"
#include "MainGameInstanceSubsystem.h"
#include "EntryWidget.generated.h"

/**
 * 
 */
class UMainGameInstanceSubsystem;

UCLASS()
class AZUREKINECT_API UEntryWidget : public UUserWidget
{
	GENERATED_BODY()

		virtual void NativeConstruct() override;
		FString GetMyIpAddress();

public:
	UFUNCTION()
		void OnClick_ServerButton();
	UFUNCTION()
		void OnClick_ClientButton();

	UPROPERTY(meta = (BindWidget))
		UButton* Server_Button;
	UPROPERTY(meta = (BindWidget))
		UButton* Client_Button;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* TextBlock_MyIP;
	UPROPERTY(meta = (BindWidget))
		UCircularThrobber* circle;

	UMainGameInstanceSubsystem* subGI;
};
