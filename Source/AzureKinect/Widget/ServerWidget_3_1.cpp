// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ServerWidget_3_1.h"
#include "Kismet/GameplayStatics.h"
#include "GuideGirlAnimInstance.h"

UServerWidget_3_1::UServerWidget_3_1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<AActor> BP_AnimMannequin(TEXT("Blueprint'/Game/Blueprints/BP_GuideGirl.BP_GuideGirl_C'"));
	GuideGirl = UGameplayStatics::GetActorOfClass(GetWorld(), BP_AnimMannequin.Class);

	static ConstructorHelpers::FObjectFinder<USoundWave> Back01(TEXT("SoundWave'/Game/Sound/Widget/배경음_01.배경음_01'"));

	Back_01 = Back01.Object;
}

void UServerWidget_3_1::NativeConstruct()
{
	Super::NativeConstruct();
	//Audio01 = UGameplayStatics::SpawnSound2D(this, Back_01);

	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	GuideAnim = Cast<UGuideGirlAnimInstance>(anim);

	GuideAnim->ButtonIndex = ButtonIndex::None;
	GuideAnim->CoachingLevel = CoachingLevel::Level_None;
	GuideAnim->WidgetIndex = WidgetIndex::ServerWidget_3_1;

	//SetMediaPath_Background();

	timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CountDown")), 21.2f, false);
}

void UServerWidget_3_1::NativeDestruct()
{
	Super::NativeDestruct();

	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	if (Cast<UGuideGirlAnimInstance>(anim)->AudioCom != NULL)
	{
		Cast<UGuideGirlAnimInstance>(anim)->AudioCom->Stop();
	}

	if (Audio01 != NULL)
		Audio01->Stop();

	UKismetSystemLibrary::K2_ClearTimerHandle(GetWorld(), timerhandle);

	GuideAnim->Count = false;

	//MediaPlayer->Close();

	this->ConditionalBeginDestroy();
}

void UServerWidget_3_1::SetMediaPath_Background()
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

void UServerWidget_3_1::CountDown()
{
	GuideAnim->Count = true;
}
