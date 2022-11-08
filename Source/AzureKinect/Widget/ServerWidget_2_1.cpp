// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ServerWidget_2_1.h"
#include "Kismet/GameplayStatics.h"
#include "GuideGirlAnimInstance.h"
#include "Components/CanvasPanelSlot.h"


UServerWidget_2_1::UServerWidget_2_1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuide01(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_89.Asset_89'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuide02(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_91.Asset_91'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuide03(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_93.Asset_93'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuide04(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_95.Asset_95'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuide05(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_97.Asset_97'"));
	TextGuide.AddUnique(TextGuide01.Object);
	TextGuide.AddUnique(TextGuide02.Object);
	TextGuide.AddUnique(TextGuide03.Object);
	TextGuide.AddUnique(TextGuide04.Object);
	TextGuide.AddUnique(TextGuide05.Object);

	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuideNum01(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_88.Asset_88'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuideNum02(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_90.Asset_90'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuideNum03(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_92.Asset_92'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuideNum04(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_94.Asset_94'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> TextGuideNum05(TEXT("Texture2D'/Game/Widget/Texture_new_/2_1/Asset_96.Asset_96'"));
	TextGuideNum.AddUnique(TextGuideNum01.Object);
	TextGuideNum.AddUnique(TextGuideNum02.Object);
	TextGuideNum.AddUnique(TextGuideNum03.Object);
	TextGuideNum.AddUnique(TextGuideNum04.Object);
	TextGuideNum.AddUnique(TextGuideNum05.Object);

	static ConstructorHelpers::FObjectFinder<USoundWave> Back04(TEXT("SoundWave'/Game/Sound/Widget/배경음_04.배경음_04'"));
	
	Back_04 = Back04.Object;

	static ConstructorHelpers::FClassFinder<AActor> BP_AnimMannequin(TEXT("Blueprint'/Game/Blueprints/BP_GuideGirl.BP_GuideGirl_C'"));
	GuideGirl = UGameplayStatics::GetActorOfClass(GetWorld(), BP_AnimMannequin.Class);

	static ConstructorHelpers::FClassFinder<AActor> ActorBGM(TEXT("Blueprint'/Game/Blueprints/BGM_01.BGM_01_C'"));
	BGM = UGameplayStatics::GetActorOfClass(GetWorld(), ActorBGM.Class);
}

void UServerWidget_2_1::NativeConstruct()
{
	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	
	Cast<UGuideGirlAnimInstance>(anim)->WidgetIndex = WidgetIndex::ServerWidget_2_1;

	loading = false;

	auto temp = Cast<UAudioComponent>(BGM->GetComponentByClass(UAudioComponent::StaticClass()));

	if (!temp->IsPlaying())
		Audio04 = UGameplayStatics::SpawnSound2D(this, Back_04);

	VideoPathes.AddUnique(FString(TEXT("./Movies/Widget/MANUAL_1.mp4")));
	VideoPathes.AddUnique(FString(TEXT("./Movies/Widget/MANUAL_2.mp4")));
	VideoPathes.AddUnique(FString(TEXT("./Movies/Widget/MANUAL_3.mp4")));
	VideoPathes.AddUnique(FString(TEXT("./Movies/Widget/MANUAL_4.mp4")));
	VideoPathes.AddUnique(FString(TEXT("./Movies/Widget/MANUAL_5.mp4")));

	//SetMediaPath_Background(FString(TEXT("./Movies/Widget/BG_dancheong.mp4")));
	SetMediaPath_Video(FString(TEXT("./Movies/Widget/MANUAL_1.mp4")));
	SetTextGuide(0);


	MaxPathIndex = VideoPathes.Num();
	CurPathIndex = 0;

	ImageVideos.AddUnique(Image_Video);
	ImageVideos.AddUnique(Image_Video2);
	ImageVideos.AddUnique(Image_Video3);
	ImageVideos.AddUnique(Image_Video4);
	ImageVideos.AddUnique(Image_Video5);

	MediaPlayers.AddUnique(MediaPlayer_Video);
	MediaPlayers.AddUnique(MediaPlayer_Video2);
	MediaPlayers.AddUnique(MediaPlayer_Video3);
	MediaPlayers.AddUnique(MediaPlayer_Video4);
	MediaPlayers.AddUnique(MediaPlayer_Video5);

	for (auto image : ImageVideos)
	{
		UCanvasPanelSlot* imageSlot = Cast<UCanvasPanelSlot>(image->Slot);

		imageSlot->SetZOrder(-2);
	}

	//SetZOrder(0);
}

void UServerWidget_2_1::NativeDestruct()
{
	if (Audio04 != NULL)
		Audio04->Stop();

	//MediaPlayer->Close();
	MediaPlayer_Video->Close();
	MediaPlayer_Video2->Close();
	MediaPlayer_Video3->Close();
	MediaPlayer_Video4->Close();
	MediaPlayer_Video5->Close();

	this->ConditionalBeginDestroy();
}

void UServerWidget_2_1::SetMediaPath_Background(FString B_path)
{
	MediaTexture = NewObject<UMediaTexture>(this);
	FileMediaSource = NewObject<UFileMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);

	FileMediaSource->SetFilePath(B_path);
	MediaPlayer->OpenSource(FileMediaSource);
	MediaPlayer->SetLooping(true);
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Background->SetBrushResourceObject(MediaTexture);
}

void UServerWidget_2_1::SetMediaPath_Video(FString video_path)
{
	if (MediaTexture_Video == nullptr)
		MediaTexture_Video = NewObject<UMediaTexture>(this);
	if (FileMediaSource_Video == nullptr)
		FileMediaSource_Video = NewObject<UFileMediaSource>(this);
	if (MediaPlayer_Video == nullptr)
		MediaPlayer_Video = NewObject<UMediaPlayer>(this);

	if (MediaTexture_Video2 == nullptr)
		MediaTexture_Video2 = NewObject<UMediaTexture>(this);
	if (FileMediaSource_Video2 == nullptr)
		FileMediaSource_Video2 = NewObject<UFileMediaSource>(this);
	if (MediaPlayer_Video2 == nullptr)
		MediaPlayer_Video2 = NewObject<UMediaPlayer>(this);

	if (MediaTexture_Video3 == nullptr)
		MediaTexture_Video3 = NewObject<UMediaTexture>(this);
	if (FileMediaSource_Video3 == nullptr)
		FileMediaSource_Video3 = NewObject<UFileMediaSource>(this);
	if (MediaPlayer_Video3 == nullptr)
		MediaPlayer_Video3 = NewObject<UMediaPlayer>(this);

	if (MediaTexture_Video4 == nullptr)
		MediaTexture_Video4 = NewObject<UMediaTexture>(this);
	if (FileMediaSource_Video4 == nullptr)
		FileMediaSource_Video4 = NewObject<UFileMediaSource>(this);
	if (MediaPlayer_Video4 == nullptr)
		MediaPlayer_Video4 = NewObject<UMediaPlayer>(this);

	if (MediaTexture_Video5 == nullptr)
		MediaTexture_Video5 = NewObject<UMediaTexture>(this);
	if (FileMediaSource_Video5 == nullptr)
		FileMediaSource_Video5 = NewObject<UFileMediaSource>(this);
	if (MediaPlayer_Video5 == nullptr)
		MediaPlayer_Video5 = NewObject<UMediaPlayer>(this);

	FileMediaSource_Video->SetFilePath(VideoPathes[0]);
	//MediaPlayer_Video->PlayOnOpen = false;
	MediaPlayer_Video->OpenSource(FileMediaSource_Video);
	MediaPlayer_Video->SetLooping(true);
	MediaTexture_Video->SetMediaPlayer(MediaPlayer_Video);
	MediaTexture_Video->UpdateResource();

	FileMediaSource_Video2->SetFilePath(VideoPathes[1]);
	//MediaPlayer_Video2->PlayOnOpen = false;
	MediaPlayer_Video2->OpenSource(FileMediaSource_Video2);
	MediaPlayer_Video2->SetLooping(true);
	MediaTexture_Video2->SetMediaPlayer(MediaPlayer_Video2);
	MediaTexture_Video2->UpdateResource();

	FileMediaSource_Video3->SetFilePath(VideoPathes[2]);
	//MediaPlayer_Video3->PlayOnOpen = false;
	MediaPlayer_Video3->OpenSource(FileMediaSource_Video3);
	MediaPlayer_Video3->SetLooping(true);
	MediaTexture_Video3->SetMediaPlayer(MediaPlayer_Video3);
	MediaTexture_Video3->UpdateResource();

	FileMediaSource_Video4->SetFilePath(VideoPathes[3]);
	//MediaPlayer_Video4->PlayOnOpen = false;
	MediaPlayer_Video4->OpenSource(FileMediaSource_Video4);
	MediaPlayer_Video4->SetLooping(true);
	MediaTexture_Video4->SetMediaPlayer(MediaPlayer_Video4);
	MediaTexture_Video4->UpdateResource();

	FileMediaSource_Video5->SetFilePath(VideoPathes[4]);
	//MediaPlayer_Video5->PlayOnOpen = false;
	MediaPlayer_Video5->OpenSource(FileMediaSource_Video5);
	MediaPlayer_Video5->SetLooping(true);
	MediaTexture_Video5->SetMediaPlayer(MediaPlayer_Video5);
	MediaTexture_Video5->UpdateResource();

	
	Image_Video->SetBrushResourceObject(MediaTexture_Video);
	Image_Video2->SetBrushResourceObject(MediaTexture_Video2);
	Image_Video3->SetBrushResourceObject(MediaTexture_Video3);
	Image_Video4->SetBrushResourceObject(MediaTexture_Video4);
	Image_Video5->SetBrushResourceObject(MediaTexture_Video5);

	UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("FirstZOrder")), 1.0f, false);
}

void UServerWidget_2_1::SetTextGuide(int32 index)
{
	Image_Guide->SetBrushFromTexture(TextGuide[index]);

	UCanvasPanelSlot* imageSlot = Cast<UCanvasPanelSlot>(Image_Guide->Slot);
	imageSlot->SetSize(FVector2D(TextGuide[index]->GetSizeX(), TextGuide[index]->GetSizeY()));

	Image_GuideNum->SetBrushFromTexture(TextGuideNum[index]);
}

void UServerWidget_2_1::SetZOrder(int32 index)
{
	for (auto MP : MediaPlayers)
	{
		MP->Pause();

		if (MP == MediaPlayers[index])
			MP->Play();
	}

	for (auto temp : ImageVideos)
	{
		UCanvasPanelSlot* imageSlot = Cast<UCanvasPanelSlot>(temp->Slot);

		if (temp == ImageVideos[index])
			imageSlot->SetZOrder(1);
		else
			imageSlot->SetZOrder(0);
	}
}

void UServerWidget_2_1::FirstZOrder()
{
	SetZOrder(0);
	loading = true;
}
