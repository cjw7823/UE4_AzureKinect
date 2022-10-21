// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ServerWidget_2_2.h"
#include "Widget/listitem.h"
#include "Kismet/GameplayStatics.h"
#include "GuideGirlAnimInstance.h"
#include "Replay_Mannequin.h"

UServerWidget_2_2::UServerWidget_2_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<AActor> BP_AnimMannequin(TEXT("Blueprint'/Game/Blueprints/BP_GuideGirl.BP_GuideGirl_C'"));
	GuideGirl = UGameplayStatics::GetActorOfClass(GetWorld(), BP_AnimMannequin.Class);

	static ConstructorHelpers::FObjectFinder<USoundWave> Back04(TEXT("SoundWave'/Game/Sound/Widget/배경음_04.배경음_04'"));

	Back_04 = Back04.Object;

	static ConstructorHelpers::FClassFinder<AActor> ActorBGM(TEXT("Blueprint'/Game/Blueprints/BGM_01.BGM_01_C'"));
	BGM = UGameplayStatics::GetActorOfClass(GetWorld(), ActorBGM.Class);
}

void UServerWidget_2_2::NativeConstruct()
{
	Super::NativeConstruct();
	//Audio01 = UGameplayStatics::SpawnSound2D(this, Back_04);

	Cast<UAudioComponent>(BGM->GetComponentByClass(UAudioComponent::StaticClass()))->Play();

	S_bar->SetVisibility(ESlateVisibility::Collapsed);

	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	Cast<UGuideGirlAnimInstance>(anim)->WidgetIndex = WidgetIndex::ServerWidget_2_2;

	for (int i = 140; i <= 190; i += 5)
	{
		auto a = CreateWidget<Ulistitem>(this, Ulistitem::StaticClass());
		a->hight = i;
		ListView_Hight->AddItem(a);
	}

	for (int j = 0; j < 2; j++)
	{
		auto b = CreateWidget<Ulistitem>(this, Ulistitem::StaticClass());
		if (j == 0)
		{
			b->hight = -1;
			b->sex = FString(TEXT("남자"));
			ListView_Sex->AddItem(b);
		}
		else
		{
			b->hight = -1;
			b->sex = FString(TEXT("여자"));
			ListView_Sex->AddItem(b);
		}
	}

	//SetMediaPath_Background();
}

void UServerWidget_2_2::NativeDestruct()
{
	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	if (Cast<UGuideGirlAnimInstance>(anim)->AudioCom != NULL)
	{
		Cast<UGuideGirlAnimInstance>(anim)->AudioCom->Stop();
	}

	Super::NativeDestruct();

	if (Audio01 != NULL)
		Audio01->Stop();

	auto temp = Cast<AReplay_Mannequin>(UGameplayStatics::GetActorOfClass(GetWorld(), AReplay_Mannequin::StaticClass()));
	temp->SetSkeletalMesh();

	//MediaPlayer->Close();

	this->ConditionalBeginDestroy();
}

void UServerWidget_2_2::SetMediaPath_Background()
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