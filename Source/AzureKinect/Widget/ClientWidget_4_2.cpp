// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_4_2.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UClientWidget_4_2::UClientWidget_4_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> Button09(TEXT("SoundWave'/Game/Sound/Widget/버튼음_09.버튼음_09'"));

	Button_09 = Button09.Object;
}

void UClientWidget_4_2::NativeConstruct()
{
	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Button_Helper->OnClicked.AddDynamic(this, &UClientWidget_4_2::OnClick_Button_Helper);

	//SetMediaPath_Background();
}

void UClientWidget_4_2::NativeDestruct()
{
	//MediaPlayer->Close();

	this->ConditionalBeginDestroy();
}

void UClientWidget_4_2::SetMediaPath_Background()
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

void UClientWidget_4_2::OnClick_Button_Helper()
{
	UGameplayStatics::PlaySound2D(this, Button_09);

	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_1]);
	temp->AddToViewport();

	UClientWidget_2_1::Index = ServerWidgetIndex::ServerWidget_4_2;
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_1);
}
