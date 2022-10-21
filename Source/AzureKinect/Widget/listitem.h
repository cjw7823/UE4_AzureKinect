// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "listitem.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API Ulistitem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (bindwidget), BlueprintReadWrite)
		UTextBlock* TextBlock_data;
	UPROPERTY(meta = (bindwidget), BlueprintReadWrite)
		UImage* Image_Back;

	int hight; // -1일경우 ListView_Sex에서 온 명령.
	FString sex;

	UObject* Thinfont;
	UObject* Thickfont;
};
