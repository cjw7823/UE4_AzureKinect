// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ClientWidget_4_3.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UClientWidget_4_3::UClientWidget_4_3(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> Button11(TEXT("SoundWave'/Game/Sound/Widget/버튼음_11.버튼음_11'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button09(TEXT("SoundWave'/Game/Sound/Widget/버튼음_09.버튼음_09'"));

	Button_11 = Button11.Object;
	Button_09 = Button09.Object;
}

void UClientWidget_4_3::NativeConstruct()
{
	Super::NativeConstruct();
	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Button_Helper->OnClicked.AddDynamic(this, &UClientWidget_4_3::OnClick_Button_Helper);
	Button_Back->OnClicked.AddDynamic(this, &UClientWidget_4_3::OnClick_Button_Back);
	Button_Retry->OnClicked.AddDynamic(this, &UClientWidget_4_3::OnClick_Button_Retry);
	Button_Next->OnClicked.AddDynamic(this, &UClientWidget_4_3::OnClick_Button_Next);

	Button_Back->SetVisibility(ESlateVisibility::Collapsed);
	Button_Retry->SetVisibility(ESlateVisibility::Collapsed);
	Button_Next->SetVisibility(ESlateVisibility::Collapsed);

	//SetMediaPath_Background();

	timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CountDown")), 3.0f, false);
}

void UClientWidget_4_3::NativeDestruct()
{
	UKismetSystemLibrary::K2_ClearTimerHandle(this, timerhandle);

	//MediaPlayer->Close();

	this->ConditionalBeginDestroy();
}

void UClientWidget_4_3::CountDown()
{
	Button_Back->SetVisibility(ESlateVisibility::Visible);
	Button_Retry->SetVisibility(ESlateVisibility::Visible);
	Button_Next->SetVisibility(ESlateVisibility::Visible);
	Image_CountdownText->SetVisibility(ESlateVisibility::Collapsed);
}

void UClientWidget_4_3::SetMediaPath_Background()
{
	MediaTexture = NewObject<UMediaTexture>(this);
	FileMediaSource = NewObject<UFileMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);

	FileMediaSource->SetFilePath(FString(TEXT("./Movies/Widget/BG_wave.mp4")));
	MediaPlayer->OpenSource(FileMediaSource);
	MediaPlayer->SetLooping(true);
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Background->SetBrushResourceObject(MediaTexture);
}

void UClientWidget_4_3::OnClick_Button_Helper()
{
	UGameplayStatics::PlaySound2D(this, Button_09);

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("OnClick_Button_Helper"));
}

void UClientWidget_4_3::OnClick_Button_Back()
{
	UGameplayStatics::PlaySound2D(this, Button_11);

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget_3_1 = CreateWidget<UClientWidget_3_1>(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_3_1]);

	if (IsValid(ClientWidget_3_1))
	{
		ClientWidget_3_1->AddToViewport();
	}
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_1);
}

void UClientWidget_4_3::OnClick_Button_Retry()
{
	UGameplayStatics::PlaySound2D(this, Button_11);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_4_3);

	Button_Back->SetVisibility(ESlateVisibility::Collapsed);
	Button_Retry->SetVisibility(ESlateVisibility::Collapsed);
	Button_Next->SetVisibility(ESlateVisibility::Collapsed);
	Image_CountdownText->SetVisibility(ESlateVisibility::Visible);
	timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CountDown")), 3.0f, false);
}

void UClientWidget_4_3::OnClick_Button_Next()
{
	UGameplayStatics::PlaySound2D(this, Button_11);


	MainPC->NextCoachingVideo();

	//MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_4_3);

	Button_Back->SetVisibility(ESlateVisibility::Collapsed);
	Button_Retry->SetVisibility(ESlateVisibility::Collapsed);
	Button_Next->SetVisibility(ESlateVisibility::Collapsed);
	Image_CountdownText->SetVisibility(ESlateVisibility::Visible);
	timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CountDown")), 3.0f, false);
}
