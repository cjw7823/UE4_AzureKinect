// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_3_3.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#define INITTIMER 180

SelectLevel UClientWidget_3_3::Level = SelectLevel::Low;
Select_Button UClientWidget_3_3::Button = Select_Button::None;

UClientWidget_3_3::UClientWidget_3_3(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> Low(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Asset_138.Asset_138'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Middle(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Asset_137.Asset_137'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> High(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Asset_136.Asset_136'"));

	if (Level == SelectLevel::Low)
	{
		TitleTexture = Low.Object;
	}
	else if (Level == SelectLevel::Middle)
	{
		TitleTexture = Middle.Object;
	}
	else if (Level == SelectLevel::High)
	{
		TitleTexture = High.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundWave> Button11(TEXT("SoundWave'/Game/Sound/Widget/버튼음_11.버튼음_11'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button09(TEXT("SoundWave'/Game/Sound/Widget/버튼음_09.버튼음_09'"));

	Button_11 = Button11.Object;
	Button_09 = Button09.Object;
}

void UClientWidget_3_3::NativeConstruct()
{
	InitTimer = 0;
	InitTimerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CheckInitTimer")), 1.0f, true);

	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Button_Helper->OnClicked.AddDynamic(this, &UClientWidget_3_3::OnClick_Button_Helper);
	Button_Back->OnClicked.AddDynamic(this, &UClientWidget_3_3::OnClick_Button_Back);
	Button_Next->OnClicked.AddDynamic(this, &UClientWidget_3_3::OnClick_Button_Next);

	Image_Title->SetBrushFromTexture(TitleTexture);

	//SetMediaPath_Background();
}

void UClientWidget_3_3::NativeDestruct()
{
	//MediaPlayer->Close();
	UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
	this->ConditionalBeginDestroy();
}

void UClientWidget_3_3::SetMediaPath_Background()
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

void UClientWidget_3_3::OnClick_Button_Helper()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_09);

	UClientWidget_2_1::Level = Level;
	UClientWidget_2_1::Button = Button;

	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_1]);
	temp->AddToViewport();

	UClientWidget_2_1::Index = ServerWidgetIndex::ServerWidget_3_3;
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_1);
}

void UClientWidget_3_3::OnClick_Button_Back()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_3_2]);
	temp->AddToViewport();

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_2, Level);
}

void UClientWidget_3_3::OnClick_Button_Next()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_4_1);

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget = CreateWidget<UClientWidget_4_1>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_4_1]);

	if (IsValid(ClientWidget))
	{
		ClientWidget->AddToViewport();
	}
}

void UClientWidget_3_3::CheckInitTimer()
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