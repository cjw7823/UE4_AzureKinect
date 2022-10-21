// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_4_1.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Widget/ClientWidget_4_2.h"

void UClientWidget_4_1::NativeConstruct()
{
	Super::NativeConstruct();
	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Button_Helper->OnClicked.AddDynamic(this, &UClientWidget_4_1::OnClick_Button_Helper);
	Button_Skip->OnClicked.AddDynamic(this, &UClientWidget_4_1::OnClick_Button_Skip);
	LimitTime = 0.f;
	SpawnWidget = false;

	//SetMediaPath_Background();
}

void UClientWidget_4_1::NativeDestruct()
{
	//MediaPlayer->Close();

	this->ConditionalBeginDestroy();
}

void UClientWidget_4_1::SetMediaPath_Background()
{
	MediaTexture = NewObject<UMediaTexture>(this);
	FileMediaSource = NewObject<UFileMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);

	FileMediaSource->SetFilePath(FString(TEXT("./Movies/Widget/BG_dancheong.mp4")));
	MediaPlayer->OpenSource(FileMediaSource);
	MediaPlayer->SetLooping(true);
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Background->SetBrushResourceObject(MediaTexture);
}

void UClientWidget_4_1::OnClick_Button_Helper()
{
	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_1]);
	temp->AddToViewport();

	UClientWidget_2_1::Index = ServerWidgetIndex::ServerWidget_4_1;
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_1);
}

void UClientWidget_4_1::OnClick_Button_Skip()
{
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_1);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto temp = CreateWidget<UClientWidget_3_1>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_3_1]);

	if (IsValid(temp))
	{
		temp->AddToViewport();
	}
}
