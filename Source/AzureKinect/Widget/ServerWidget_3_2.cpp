// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ServerWidget_3_2.h"
#include "Kismet/GameplayStatics.h"
#include "GuideGirlAnimInstance.h"
#include "MainPlayerController.h"

UServerWidget_3_2::UServerWidget_3_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> Low_Title(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_98.Asset_98'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Middle_Title(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_100.Asset_100'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> High_Title(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_101.Asset_101'"));
	LowTitle = Low_Title.Object;
	MiddleTitle = Middle_Title.Object;
	HighTitle = High_Title.Object;


	static ConstructorHelpers::FClassFinder<AActor> BP_AnimMannequin(TEXT("Blueprint'/Game/Blueprints/BP_GuideGirl.BP_GuideGirl_C'"));
	GuideGirl = UGameplayStatics::GetActorOfClass(GetWorld(), BP_AnimMannequin.Class);

	static ConstructorHelpers::FObjectFinder<USoundWave> Back01(TEXT("SoundWave'/Game/Sound/Widget/배경음_01.배경음_01'"));

	Back_01 = Back01.Object;
}

void UServerWidget_3_2::NativeConstruct()
{
	auto ClinetPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 1));
	if (ClinetPC->Level == SelectLevel::Low)
		Image_Title->SetBrushFromTexture(LowTitle);
	else if(ClinetPC->Level == SelectLevel::Middle)
		Image_Title->SetBrushFromTexture(MiddleTitle);
	else if (ClinetPC->Level == SelectLevel::High)
		Image_Title->SetBrushFromTexture(HighTitle);


	//Audio01 = UGameplayStatics::SpawnSound2D(this, Back_01);

	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	auto temp = Cast<UGuideGirlAnimInstance>(anim);

	temp->WidgetIndex = WidgetIndex::ServerWidget_3_2;

	//SetMediaPath_Background();
}

void UServerWidget_3_2::NativeDestruct()
{
	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	if (Cast<UGuideGirlAnimInstance>(anim)->AudioCom != NULL)
	{
		Cast<UGuideGirlAnimInstance>(anim)->AudioCom->Stop();
	}

	if (Audio01 != NULL)
		Audio01->Stop();

	//MediaPlayer->Close();

	this->ConditionalBeginDestroy();
}

void UServerWidget_3_2::SetMediaPath_Background()
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