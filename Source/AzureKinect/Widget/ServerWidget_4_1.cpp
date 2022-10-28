// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ServerWidget_4_1.h"
#include "Engine/SceneCapture2D.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameInstance.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UServerWidget_4_1::UServerWidget_4_1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UMaterial> UserMaterial(TEXT("Material'/Game/Widget/M_User_RenderTarget2D.M_User_RenderTarget2D'"));
	User_Material = UserMaterial.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> Back06(TEXT("SoundWave'/Game/Sound/Widget/배경음_06.배경음_06'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Warning03(TEXT("SoundWave'/Game/Sound/Widget/경고_03.경고_03'"));

	Back_06 = Back06.Object;
	Warning_03 = Warning03.Object;

	static ConstructorHelpers::FClassFinder<AActor> User(TEXT("Blueprint'/Game/Blueprints/BP_User_Doll.BP_User_Doll_C'"));

	UserDoll = UGameplayStatics::GetActorOfClass(GetWorld(), User.Class);
}


void UServerWidget_4_1::NativeConstruct()
{
	Skel = Cast<USkeletalMeshComponent>(UserDoll->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	Image_Sequence->SetVisibility(ESlateVisibility::Collapsed);

	Audio01 = UGameplayStatics::SpawnSound2D(this, Back_06);

	Percent = 0;
	time = 0;
	warning = false;
	MainGM = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ClientMainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 1));

	//Image_User->SetBrushFromMaterial(User_Material);
	FLinearColor temp = FLinearColor(0, 0, 0, 0);
	Image_User->SetColorAndOpacity(temp);

	//SetMediaPath_Sequence();

	//3초 후부터 스켈레톤 체크
	timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CheckSkeleton")), 0.05f, true, 3.0f);

	//시퀀스 재생
	UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("PlaySequence")), 3.0f, false);
	UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("ShowSequence")), 3.5f, false);
}

void UServerWidget_4_1::NativeDestruct()
{
	if (Audio01 != NULL)
		Audio01->Stop();

	UKismetSystemLibrary::K2_ClearTimerHandle(GetWorld(), timerhandle);

	if(!MediaPlayer->IsClosed())
		MediaPlayer->Close();

	this->ConditionalBeginDestroy();
}

void UServerWidget_4_1::CheckSkeleton()
{
	bool PoseCheck = false;

	FRotator upperarm_l = Skel->GetBoneQuaternion(FName("upperarm_l"), EBoneSpaces::ComponentSpace).Rotator();
	FRotator lowerarm_l = Skel->GetBoneQuaternion(FName("lowerarm_l"), EBoneSpaces::ComponentSpace).Rotator();
	FRotator upperarm_r = Skel->GetBoneQuaternion(FName("upperarm_r"), EBoneSpaces::ComponentSpace).Rotator();
	FRotator lowerarm_r = Skel->GetBoneQuaternion(FName("lowerarm_r"), EBoneSpaces::ComponentSpace).Rotator();
	FRotator thigh_l = Skel->GetBoneQuaternion(FName("thigh_l"), EBoneSpaces::ComponentSpace).Rotator();
	FRotator calf_l = Skel->GetBoneQuaternion(FName("calf_l"), EBoneSpaces::ComponentSpace).Rotator();
	FRotator thigh_r = Skel->GetBoneQuaternion(FName("thigh_r"), EBoneSpaces::ComponentSpace).Rotator();
	FRotator calf_r = Skel->GetBoneQuaternion(FName("calf_r"), EBoneSpaces::ComponentSpace).Rotator();
	//포즈 체크
	float tolerance = 50.0f;
	if (//상체
		upperarm_l.Equals(FRotator(-3.8f, 1.8f, -95.0f), tolerance) &&
		lowerarm_l.Equals(FRotator(22.0f, -10.0f, -106.0f), tolerance) &&
		upperarm_r.Equals(FRotator(10.6f, -8.6f, 86.0f), tolerance) &&
		lowerarm_r.Equals(FRotator(-1.1f, 1.6f, 90.3f), tolerance) //&&

		//하체
		/*thigh_l.Equals(FRotator(7.1f, -89.1f, -73.5f), tolerance) &&
		calf_l.Equals(FRotator(15.3f, -87.5f, -80.8f), tolerance) &&
		thigh_r.Equals(FRotator(-7.9f, 89.3f, 98.1f), tolerance) &&
		calf_r.Equals(FRotator(-23.3f, 88.5f, 98.0f), tolerance)*/)
	{
		PoseCheck = true;
	}


	if (PoseCheck && MainGM->TrackedSkeleton_Num == 1 && Percent < 100)
	{
		ClientMainPC->DeltaRotation = true;
		warning = false;
		Percent++;

		if (MediaPlayer->IsPaused())
			MediaPlayer->Play();
	}
	else if (!warning)
	{
		ClientMainPC->DeltaRotation = false;
		warning = true;
		UGameplayStatics::PlaySound2D(this, Warning_03);

		if (MediaPlayer->IsPlaying())
			MediaPlayer->Pause();
	}
	else
	{
		ClientMainPC->DeltaRotation = false;
		warning = true;

		if (MediaPlayer->IsPlaying())
			MediaPlayer->Pause();
	}

	if (Percent >= 100)
	{
		ClientMainPC->DeltaRotation = false;

		UKismetSystemLibrary::K2_ClearTimerHandle(GetWorld(), timerhandle);

		UWidgetLayoutLibrary::RemoveAllWidgets(this);

		ClientMainPC->ShowClientWidget(ClientWidgetIndex::ClientWidget_4_2);

		ClientMainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_4_2);
	}
}

void UServerWidget_4_1::PlaySequence()
{
	SetMediaPath_Sequence();
}

void UServerWidget_4_1::ShowSequence()
{
	Image_Sequence->SetVisibility(ESlateVisibility::Visible);
}

void UServerWidget_4_1::SetMediaPath_Sequence()
{
	MediaTexture = NewObject<UMediaTexture>(this);
	MediaSource = NewObject<UImgMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);

	FString Path = FPaths::ProjectContentDir() + FString(TEXT("Movies/Widget/HumanWater/Human Water_00000.png"));
	MediaSource->SetSequencePath(Path);
	MediaSource->SetSequencePath(Path);
	MediaSource->FrameRateOverride = FFrameRate(70, 1);
	//MediaPlayer->OnPlaybackResumed.AddDynamic(this, &UServerWidget_4_1::OnPlaybackResumed);
	MediaPlayer->SetLooping(true);
	MediaPlayer->OpenSource(MediaSource);

	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Sequence->SetBrushResourceObject(MediaTexture);
}

FText UServerWidget_4_1::Textbinding()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("%d"), Percent));
	FString temp;
	temp.Append(FString::FromInt(Percent));
	temp.Append(TEXT("%"));
	return FText::FromString(temp);
}