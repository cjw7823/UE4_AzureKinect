// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_1_1.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

bool UClientWidget_1_1::isFirst = true;

void UClientWidget_1_1::NativeConstruct()
{
	MainPC = MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Image_touch->OnMouseButtonDownEvent.BindUFunction(this, FName(TEXT("MouseDown")));

	SetMediaPath_Background();
}

void UClientWidget_1_1::NativeDestruct()
{
	/*MediaPlayer->Pause();
	MediaPlayer->Close();*/
	MediaPlayer->ConditionalBeginDestroy();

	this->ConditionalBeginDestroy();
}

void UClientWidget_1_1::SetMediaPath_Background()
{
	/*MediaTexture = NewObject<UMediaTexture>(this);
	FileMediaSource = NewObject<UFileMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);

	FileMediaSource->SetFilePath(FString(TEXT("./Movies/Widget/EEUM_LOGO_MOTION.mp4")));
	MediaPlayer->OpenSource(FileMediaSource);
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Background->SetBrushResourceObject(MediaTexture);*/

	MediaTexture = NewObject<UMediaTexture>(this);
	MediaSource = NewObject<UImgMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);

	FString Path = FPaths::ProjectContentDir() + FString(TEXT("Movies/Widget/Entry/BG_10000.png"));
	MediaSource->SetSequencePath(Path);
	MediaSource->FrameRateOverride = FFrameRate(60, 1);
	//MediaPlayer->OnPlaybackResumed.AddDynamic(this, &UClientWidget_1_1::OnPlaybackResumed);
	MediaPlayer->SetLooping(true);
	MediaPlayer->OpenSource(MediaSource);

	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Background->SetBrushResourceObject(MediaTexture);
}

void UClientWidget_1_1::OnPlaybackResumed()
{
	float seconds = (float)MediaPlayer->GetDuration().GetTotalSeconds() - 0.5f;
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, FString::Printf(TEXT("%f"), seconds));

	UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("EndPlay")), seconds, false);
}

void UClientWidget_1_1::EndPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("EndPlay"));

	MediaPlayer->Pause();
}

void UClientWidget_1_1::MouseDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	if (isFirst)
	{
		MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_1);
		UWidgetLayoutLibrary::RemoveAllWidgets(this);

		auto ClientWidget = CreateWidget<UClientWidget_2_1>(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_1]);

		if (IsValid(ClientWidget))
		{
			ClientWidget->AddToViewport();
		}
		isFirst = false;
	}
	else
	{
		MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_3);
		UWidgetLayoutLibrary::RemoveAllWidgets(this);

		auto ClientWidget = CreateWidget<UClientWidget_2_3>(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_3]);

		if (IsValid(ClientWidget))
		{
			ClientWidget->AddToViewport();
		}
	}
}