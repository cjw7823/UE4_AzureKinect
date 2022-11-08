// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_5_1.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#define INITTIMER 180

UClientWidget_5_1::UClientWidget_5_1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> Button11(TEXT("SoundWave'/Game/Sound/Widget/버튼음_11.버튼음_11'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button09(TEXT("SoundWave'/Game/Sound/Widget/버튼음_09.버튼음_09'"));

	Button_11 = Button11.Object;
	Button_09 = Button09.Object;
}

void UClientWidget_5_1::NativeConstruct()
{
	InitTimer = 0;
	InitTimerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CheckInitTimer")), 1.0f, true);

	//Super::NativeConstruct();

	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Image_lastcut->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_Score->SetVisibility(ESlateVisibility::Collapsed);

	Button_Helper->OnClicked.AddDynamic(this, &UClientWidget_5_1::OnClick_Button_Helper);
	Button_Retry->OnClicked.AddDynamic(this, &UClientWidget_5_1::OnClick_Button_Retry);
	Button_DetailCoaching->OnClicked.AddDynamic(this, &UClientWidget_5_1::OnClick_Button_DetailCoaching);
	Button_NextLevel->OnClicked.AddDynamic(this, &UClientWidget_5_1::OnClick_Button_NextLevel);

	//SetMediaPath_Background();
	SetMediaPath_RollingNumber();

	timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString("SetScoreText"), 0.5f, true);
}

void UClientWidget_5_1::NativeDestruct()
{
	//Super::NativeDestruct();

	UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
	UKismetSystemLibrary::K2_ClearTimerHandle(this, timerhandle);

	//MediaPlayer->Close();
	MediaPlayer_Rolling->Close();

	this->ConditionalBeginDestroy();
}

void UClientWidget_5_1::SetMediaPath_Background()
{
	if (MediaTexture == nullptr)
		MediaTexture = NewObject<UMediaTexture>(this);
	if (FileMediaSource == nullptr)
		FileMediaSource = NewObject<UFileMediaSource>(this);
	if (MediaPlayer == nullptr)
		MediaPlayer = NewObject<UMediaPlayer>(this);

	FileMediaSource->SetFilePath(FString(TEXT("./Movies/Widget/BG_wave.mp4")));
	MediaPlayer->OpenSource(FileMediaSource);
	MediaPlayer->SetLooping(true);
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Background->SetBrushResourceObject(MediaTexture);
}

void UClientWidget_5_1::SetMediaPath_RollingNumber()
{
	MediaTexture_Rolling = NewObject<UMediaTexture>(this);
	MediaSource_Rolling = NewObject<UImgMediaSource>(this);
	MediaPlayer_Rolling = NewObject<UMediaPlayer>(this);

	FString Path = FPaths::ProjectContentDir() + FString(TEXT("Movies/Widget/RollingNumber/Rolling Number_00000.png"));
	MediaSource_Rolling->SetSequencePath(Path);
	MediaSource_Rolling->FrameRateOverride = FFrameRate(60, 1);
	MediaPlayer_Rolling->OnPlaybackResumed.AddDynamic(this, &UClientWidget_5_1::OnPlaybackResumed);
	MediaPlayer_Rolling->SetLooping(true);
	MediaPlayer_Rolling->OpenSource(MediaSource_Rolling);

	MediaTexture_Rolling->SetMediaPlayer(MediaPlayer_Rolling);
	MediaTexture_Rolling->UpdateResource();
	Image_Rolling->SetBrushResourceObject(MediaTexture_Rolling);
}

void UClientWidget_5_1::OnPlaybackResumed()
{
	float seconds = (float)MediaPlayer_Rolling->GetDuration().GetTotalSeconds() - 0.5f;
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, FString::Printf(TEXT("%f"), seconds));

	UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("EndPlay")), seconds, false);
}

void UClientWidget_5_1::EndPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("EndPlay"));

	MediaPlayer_Rolling->Pause();
	Image_lastcut->SetVisibility(ESlateVisibility::Visible);
	Image_Rolling->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_Score->SetVisibility(ESlateVisibility::Visible);
}

void UClientWidget_5_1::OnClick_Button_Helper()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_09);

	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_1]);
	temp->AddToViewport();

	UClientWidget_2_1::Index = ServerWidgetIndex::ServerWidget_5_1;
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_1);
}

void UClientWidget_5_1::OnClick_Button_Retry()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget_3_1 = CreateWidget<UClientWidget_3_1>(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_3_1]);

	if (IsValid(ClientWidget_3_1))
	{
		ClientWidget_3_1->AddToViewport();
	}
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_1);
}

void UClientWidget_5_1::OnClick_Button_DetailCoaching()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget = CreateWidget<UClientWidget_5_2>(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_5_2]);

	if (IsValid(ClientWidget))
	{
		ClientWidget->AddToViewport();
		MainPC->ClientWidget_5_2 = ClientWidget;
	}
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_5_2);
}

void UClientWidget_5_1::OnClick_Button_NextLevel()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	MainPC->NextCoachingVideo();

	MainPC->ShowClientWidget(ClientWidgetIndex::ClientWidget_4_2);

}

void UClientWidget_5_1::SetScoreText()
{
	if (FString::FromInt(MainPC->score) != TextBlock_Score->GetText().ToString())
	{
		FText text = FText::FromString(FString::FromInt(MainPC->score));
		TextBlock_Score->SetText(text);
	}
}

void UClientWidget_5_1::CheckInitTimer()
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