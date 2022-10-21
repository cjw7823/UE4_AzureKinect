// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ServerWidget_4_2.h"
#include "MainPlayerController.h"
#include "AzureKinectManager.h"
#include "GuideGirlAnimInstance.h"

UServerWidget_4_2::UServerWidget_4_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<AActor> BP_AnimMannequin(TEXT("Blueprint'/Game/Blueprints/BP_GuideGirl.BP_GuideGirl_C'"));
	GuideGirl = UGameplayStatics::GetActorOfClass(GetWorld(), BP_AnimMannequin.Class);
}

void UServerWidget_4_2::NativeConstruct()
{
	Super::NativeConstruct();
	ClientMainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 1));

	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	Cast<UGuideGirlAnimInstance>(anim)->WidgetIndex = WidgetIndex::ServerWidget_4_2;

	//SetMediaPath_Background();

	timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CountDown")), 8.0f, false);
}

void UServerWidget_4_2::NativeDestruct()
{
	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	if (Cast<UGuideGirlAnimInstance>(anim)->AudioCom != NULL)
	{
		Cast<UGuideGirlAnimInstance>(anim)->AudioCom->Stop();
	}

	UKismetSystemLibrary::K2_ClearTimerHandle(GetWorld(), timerhandle);

	//MediaPlayer->Close();

	this->ConditionalBeginDestroy();
}

void UServerWidget_4_2::SetMediaPath_Background()
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

void UServerWidget_4_2::CountDown()
{
	ClientMainPC->ShowClientWidget(ClientWidgetIndex::ClientWidget_4_3);

	ClientMainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_4_3);
}
