// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ServerWidget_5_1.h"
#include "Kismet/GameplayStatics.h"
#include "GuideGirlAnimInstance.h"
#include "/work/ue4_azure_kinect/Source/AzureKinect/Widget/Referee.h"

UServerWidget_5_1::UServerWidget_5_1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<AActor> BP_AnimMannequin(TEXT("Blueprint'/Game/Blueprints/BP_GuideGirl.BP_GuideGirl_C'"));
	GuideGirl = UGameplayStatics::GetActorOfClass(GetWorld(), BP_AnimMannequin.Class);

	auto pc = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	referee = pc->GetReferee();

	static ConstructorHelpers::FObjectFinder<USoundWave> ScoreBoard02(TEXT("SoundWave'/Game/Sound/Widget/점수창_02.점수창_02'"));

	ScoreBoard_02 = ScoreBoard02.Object;
}

void UServerWidget_5_1::NativeConstruct()
{
	Super::NativeConstruct();
	TotalScore = 0;
	Image_lastcut->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_Score->SetVisibility(ESlateVisibility::Collapsed);

	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	Cast<UGuideGirlAnimInstance>(anim)->WidgetIndex = WidgetIndex::ServerWidget_5_1;

	//SetMediaPath_Background();
	SetMediaPath_RollingNumber();

	if (referee != NULL)
		Scoring();
	else
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("referee is nullptr!!!!!!!!!!!!!"));

	//Scoring() 이후에 소리 재생
	UGameplayStatics::PlaySound2D(this, ScoreBoard_02);
}

void UServerWidget_5_1::SetMediaPath_Background()
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

void UServerWidget_5_1::SetMediaPath_RollingNumber()
{
	if (MediaTexture_Rolling == nullptr)
		MediaTexture_Rolling = NewObject<UMediaTexture>(this);
	if (MediaSource_Rolling == nullptr)
		MediaSource_Rolling = NewObject<UImgMediaSource>(this);
	if (MediaPlayer_Rolling == nullptr)
		MediaPlayer_Rolling = NewObject<UMediaPlayer>(this);

	FString Path = FPaths::ProjectContentDir() + FString(TEXT("Movies/Widget/RollingNumber/Rolling Number_00000.png"));
	MediaSource_Rolling->SetSequencePath(Path);
	MediaSource_Rolling->FrameRateOverride = FFrameRate(60, 1);
	MediaPlayer_Rolling->OnPlaybackResumed.AddDynamic(this, &UServerWidget_5_1::OnPlaybackResumed);
	MediaPlayer_Rolling->SetLooping(true);
	MediaPlayer_Rolling->OpenSource(MediaSource_Rolling);

	MediaTexture_Rolling->SetMediaPlayer(MediaPlayer_Rolling);
	MediaTexture_Rolling->UpdateResource();
	Image_Rolling->SetBrushResourceObject(MediaTexture_Rolling);
}

void UServerWidget_5_1::NativeDestruct()
{
	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	if (Cast<UGuideGirlAnimInstance>(anim)->AudioCom != NULL)
	{
		Cast<UGuideGirlAnimInstance>(anim)->AudioCom->Stop();
	}

	//auto ClientPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 1));
	//ClientPC->score = 0;

	//MediaPlayer->Close();
	if (!MediaPlayer_Rolling->IsClosed())
		MediaPlayer_Rolling->Close();

	this->ConditionalBeginDestroy();
}

void UServerWidget_5_1::Scoring()
{
	referee->Scoring();

	SetTotalScore();
}

void UServerWidget_5_1::OnPlaybackResumed()
{
	float seconds = (float)MediaPlayer_Rolling->GetDuration().GetTotalSeconds() - 0.5f;
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, FString::Printf(TEXT("%f"), seconds));

	UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("EndPlay")), seconds, false);
}

void UServerWidget_5_1::EndPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("EndPlay"));

	MediaPlayer_Rolling->Pause();
	Image_lastcut->SetVisibility(ESlateVisibility::Visible);
	Image_Rolling->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_Score->SetVisibility(ESlateVisibility::Visible);

	if(!MediaPlayer_Rolling->IsClosed())
		MediaPlayer_Rolling->Close();
}

void UServerWidget_5_1::SetTotalScore()
{
	if (referee->Done_Scoring)
	{
		auto ClientPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 1));

		TotalScore = referee->GetTotalScore();

		TextBlock_Score->SetText(FText::FromString(FString::FromInt(TotalScore)));

		ClientPC->score = TotalScore;

		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Orange, FString::Printf(TEXT("TotalScore : %d"), TotalScore));
	}
	else
	{
		UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("SetTotalScore")), 0.1f, false);
	}
}
