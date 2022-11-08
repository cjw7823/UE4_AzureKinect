// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_3_1.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#define INITTIMER 180

UClientWidget_3_1::UClientWidget_3_1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> Button14(TEXT("SoundWave'/Game/Sound/Widget/버튼음_11.버튼음_11'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button09(TEXT("SoundWave'/Game/Sound/Widget/버튼음_09.버튼음_09'"));

	Button_11 = Button14.Object;
	Button_09 = Button09.Object;
}

void UClientWidget_3_1::NativeConstruct()
{
	InitTimer = 0;
	InitTimerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CheckInitTimer")), 1.0f, true);

	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Button_LowLevel->OnClicked.AddDynamic(this, &UClientWidget_3_1::OnClick_Button_LowLevel);
	Button_MiddleLevel->OnClicked.AddDynamic(this, &UClientWidget_3_1::OnClick_Button_MiddleLevel);
	Button_HighLevel->OnClicked.AddDynamic(this, &UClientWidget_3_1::OnClick_Button_HighLevel);
	Button_Helper->OnClicked.AddDynamic(this, &UClientWidget_3_1::OnClick_Button_Helper);
	Button_Back->OnClicked.AddDynamic(this, &UClientWidget_3_1::OnClick_Button_Back);

	Button_LowLevel->OnPressed.AddDynamic(this, &UClientWidget_3_1::OnPressed_Button_LowLevel);
	Button_MiddleLevel->OnPressed.AddDynamic(this, &UClientWidget_3_1::OnPressed_Button_MiddleLevel);
	Button_HighLevel->OnPressed.AddDynamic(this, &UClientWidget_3_1::OnPressed_Button_HighLevel);
	Button_LowLevel->OnReleased.AddDynamic(this, &UClientWidget_3_1::OnReleased_Button);
	Button_MiddleLevel->OnReleased.AddDynamic(this, &UClientWidget_3_1::OnReleased_Button);
	Button_HighLevel->OnReleased.AddDynamic(this, &UClientWidget_3_1::OnReleased_Button);

	//SetMediaPath_Background();
}

void UClientWidget_3_1::NativeDestruct()
{
	//MediaPlayer->Close();
	UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
	this->ConditionalBeginDestroy();
}

void UClientWidget_3_1::SetMediaPath_Background()
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

void UClientWidget_3_1::OnClick_Button_LowLevel()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	UClientWidget_3_2::Level = SelectLevel::Low;
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto temp = Cast<UClientWidget_3_2>(CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_3_2]));
	temp->AddToViewport();
	
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_2, SelectLevel::Low);
}

void UClientWidget_3_1::OnClick_Button_MiddleLevel()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	UClientWidget_3_2::Level = SelectLevel::Middle;
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto temp = Cast<UClientWidget_3_2>(CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_3_2]));
	temp->AddToViewport();
	
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_2, SelectLevel::Middle);
}

void UClientWidget_3_1::OnClick_Button_HighLevel()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	UClientWidget_3_2::Level = SelectLevel::High;
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto temp = Cast<UClientWidget_3_2>(CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_3_2]));
	temp->AddToViewport();
	
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_2, SelectLevel::High);
}

void UClientWidget_3_1::OnClick_Button_Helper()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_09);

	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_1]);
	temp->AddToViewport();

	UClientWidget_2_1::Index = ServerWidgetIndex::ServerWidget_3_1;
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_1);
}

void UClientWidget_3_1::OnClick_Button_Back()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_3]);
	temp->AddToViewport();

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_3);
}

void UClientWidget_3_1::OnPressed_Button_LowLevel()
{
	InitTimer = 0;
	MainPC->ClickButton_3_1_Pressed(FString(TEXT("LowLevel")));
}

void UClientWidget_3_1::OnPressed_Button_MiddleLevel()
{
	InitTimer = 0;
	MainPC->ClickButton_3_1_Pressed(FString(TEXT("MiddleLevel")));
}

void UClientWidget_3_1::OnPressed_Button_HighLevel()
{
	InitTimer = 0;
	MainPC->ClickButton_3_1_Pressed(FString(TEXT("HighLevel")));
}

void UClientWidget_3_1::OnReleased_Button()
{
	InitTimer = 0;
	MainPC->ClickButton_3_1_Released();
}

void UClientWidget_3_1::CheckInitTimer()
{
	InitTimer += 1;

	if (InitTimer >= INITTIMER)
	{
		UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
		UClientWidget_1_1::isFirst = true;
		UClientWidget_2_1::isFirst = true;

		MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_1_1);
		UWidgetLayoutLibrary::RemoveAllWidgets(this);
		auto temp = CreateWidget<UClientWidget_1_1>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_1_1]);

		if (IsValid(temp))
		{
			temp->AddToViewport();
		}
	}
}

#undef INITTIMER