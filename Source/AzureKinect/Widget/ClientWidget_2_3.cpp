// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_2_3.h"
#include "Widget/ClientWidget_2_1.h"
#include "Widget/ClientWidget_2_2.h"
#include "Widget/ClientWidget_3_1.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#define INITTIMER 60

UClientWidget_2_3::UClientWidget_2_3(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> Button14(TEXT("SoundWave'/Game/Sound/Widget/버튼음_14.버튼음_14'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button09(TEXT("SoundWave'/Game/Sound/Widget/버튼음_09.버튼음_09'"));

	Button_14 = Button14.Object;
	Button_09 = Button09.Object;
}

void UClientWidget_2_3::NativeConstruct()
{
	InitTimer = 0;
	InitTimerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CheckInitTimer")), 1.0f, true);

	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Button_Userdata->OnClicked.AddDynamic(this, &UClientWidget_2_3::OnClick_Button_Userdata);
	Button_Enter->OnClicked.AddDynamic(this, &UClientWidget_2_3::OnClick_Button_Enter);
	Button_Helper->OnClicked.AddDynamic(this, &UClientWidget_2_3::OnClick_Button_Helper);
	Button_Userdata->OnPressed.AddDynamic(this, &UClientWidget_2_3::OnPressed_Button_Userdata);
	Button_Enter->OnPressed.AddDynamic(this, &UClientWidget_2_3::OnPressed_Button_Enter);
	Button_Userdata->OnReleased.AddDynamic(this, &UClientWidget_2_3::OnReleased_Button);
	Button_Enter->OnReleased.AddDynamic(this, &UClientWidget_2_3::OnReleased_Button);


	//SetMediaPath_Background();
}

void UClientWidget_2_3::NativeDestruct()
{
	//MediaPlayer->Close();
	UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
	this->ConditionalBeginDestroy();
}

void UClientWidget_2_3::SetMediaPath_Background()
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

void UClientWidget_2_3::OnClick_Button_Userdata()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_14);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_2);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	UClientWidget_2_2* temp = CreateWidget<UClientWidget_2_2>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_2_2]);

	if (IsValid(temp))
	{
		temp->AddToViewport();
	}
}

void UClientWidget_2_3::OnClick_Button_Enter()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_14);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_1);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	UClientWidget_3_1* temp = CreateWidget<UClientWidget_3_1>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_3_1]);

	if (IsValid(temp))
	{
		temp->AddToViewport();
	}
}

void UClientWidget_2_3::OnClick_Button_Helper()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_09);

	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_1]);
	temp->AddToViewport();

	UClientWidget_2_1::Index = ServerWidgetIndex::ServerWidget_2_3;
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_1);
}

void UClientWidget_2_3::OnPressed_Button_Userdata()
{
	InitTimer = 0;
	MainPC->ClickButton_2_3_Pressed(FString(TEXT("Userdata")));
}

void UClientWidget_2_3::OnPressed_Button_Enter()
{
	InitTimer = 0;
	MainPC->ClickButton_2_3_Pressed(FString(TEXT("Enter")));
}

void UClientWidget_2_3::OnReleased_Button()
{
	InitTimer = 0;
	MainPC->ClickButton_2_3_Released();
}

void UClientWidget_2_3::CheckInitTimer()
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