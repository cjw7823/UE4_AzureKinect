// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/listitem.h"

void Ulistitem::NativeConstruct()
{
	Super::NativeConstruct();
	
	/*ConstructorHelpers::FObjectFinder<UObject> Thin(TEXT("Font'/Game/Widget/Font/AppleSDGothicNeoR_Font.AppleSDGothicNeoR_Font'"));
	ConstructorHelpers::FObjectFinder<UObject> Thick(TEXT("Font'/Game/Widget/Font/AppleSDGothicNeoSB_Font.AppleSDGothicNeoSB_Font'"));

	if (!Thin.Succeeded() || !Thick.Succeeded())
	{
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Font not found!"));
	}

	Thinfont = Thin.Object;
	Thickfont = Thick.Object;*/

	Image_Back->SetVisibility(ESlateVisibility::Collapsed);
}

void Ulistitem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Image_Back->SetVisibility(ESlateVisibility::Collapsed);
	if (IsListItemSelected())
	{
		Image_Back->SetVisibility(ESlateVisibility::Visible);
	}
}

void Ulistitem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	Ulistitem* temp = Cast<Ulistitem>(ListItemObject);
	if (temp->hight == -1)
	{
		FText text = FText::FromString(temp->sex);
		TextBlock_data->SetText(text);
	}
	else
	{
		if (temp->hight <= 140)
		{
			auto Text = FText::FromString(TEXT("140cm 이하"));
			TextBlock_data->SetText(Text);
		}
		else if (temp->hight >= 190)
		{
			auto Text = FText::FromString(TEXT("190cm 이상"));
			TextBlock_data->SetText(Text);
		}
		else
		{
			auto Text = FText::FromString(FString::Printf(TEXT("%dcm"), temp->hight));
			TextBlock_data->SetText(Text);
		}
	}
}
