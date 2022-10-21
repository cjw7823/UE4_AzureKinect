// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ServerWidget_1_1.h"
#include "Kismet/GameplayStatics.h"

UServerWidget_1_1::UServerWidget_1_1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> Back02(TEXT("SoundWave'/Game/Sound/Widget/배경음_02.배경음_02'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Transition04(TEXT("SoundWave'/Game/Sound/Widget/트랜지션_04.트랜지션_04'"));
	Back_02 = Back02.Object;
	Transition_04 = Transition04.Object;

	static ConstructorHelpers::FClassFinder<AActor> ActorBGM(TEXT("Blueprint'/Game/Blueprints/BGM_01.BGM_01_C'"));
	BGM = UGameplayStatics::GetActorOfClass(GetWorld(), ActorBGM.Class);
}

void UServerWidget_1_1::NativeConstruct()
{
	Super::NativeConstruct();

	auto temp = Cast<UAudioComponent>(BGM->GetComponentByClass(UAudioComponent::StaticClass()));

	if(temp->IsPlaying())
		temp->Stop();

	Image_main->SetVisibility(ESlateVisibility::Visible);
	Image_main2->SetVisibility(ESlateVisibility::Visible);
	SetMediaPath_Background();

	Audio01 = UGameplayStatics::SpawnSound2D(this, Back_02);

	timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("OpenDoor")), 5.0f, false);
}

void UServerWidget_1_1::NativeDestruct()
{
	if(Audio01 != NULL)
		Audio01->Stop();
	if (Audio02 != NULL)
		Audio02->Stop();

	UKismetSystemLibrary::K2_ClearTimerHandle(GetWorld(), timerhandle);

	this->ConditionalBeginDestroy();
}

void UServerWidget_1_1::SetMediaPath_Background()
{
	MediaTexture = NewObject<UMediaTexture>(this);
	MediaSource = NewObject<UImgMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);

	FString Path = FPaths::ProjectContentDir() + FString(TEXT("Movies/Widget/Entry/BG_10000.png"));
	MediaSource->SetSequencePath(Path);
	MediaSource->FrameRateOverride = FFrameRate(60, 1);
	//MediaPlayer->OnPlaybackResumed.AddDynamic(this, &UServerWidget_1_1::OnPlaybackResumed);
	MediaPlayer->SetLooping(true);
	MediaPlayer->OpenSource(MediaSource);

	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Background->SetBrushResourceObject(MediaTexture);
}

void UServerWidget_1_1::OnPlaybackResumed()
{
	float seconds = (float)MediaPlayer->GetDuration().GetTotalSeconds() - 0.5f;
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, FString::Printf(TEXT("%f"), seconds));

	UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("EndPlay")), seconds, false);
}

void UServerWidget_1_1::EndPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("EndPlay"));

	MediaPlayer->Pause();
}

void UServerWidget_1_1::OpenDoor()
{
	Audio02 = UGameplayStatics::SpawnSound2D(this, Transition_04);

	UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("Dissolve")), 0.01f, false);

}

void UServerWidget_1_1::Dissolve()
{
	float alpha = Image_main->ColorAndOpacity.A - 0.01;

	FLinearColor temp = FLinearColor(1, 1, 1, alpha);

	Image_main->SetColorAndOpacity(temp);
	Image_main2->SetColorAndOpacity(temp);

	if (alpha > 0)
	{
		UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("Dissolve")), 0.01f, false);
	}
}
