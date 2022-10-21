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
	bool PoseCheck = true;

	FRotator upperarm_l = Skel->GetBoneQuaternion(FName("upperarm_l")).Rotator();
	FRotator lowerarm_l = Skel->GetBoneQuaternion(FName("lowerarm_l")).Rotator();
	FRotator upperarm_r = Skel->GetBoneQuaternion(FName("upperarm_r")).Rotator();
	FRotator lowerarm_r = Skel->GetBoneQuaternion(FName("lowerarm_r")).Rotator();
	FRotator thigh_l = Skel->GetBoneQuaternion(FName("thigh_l")).Rotator();
	FRotator calf_l = Skel->GetBoneQuaternion(FName("calf_l")).Rotator();
	FRotator thigh_r = Skel->GetBoneQuaternion(FName("thigh_r")).Rotator();
	FRotator calf_r = Skel->GetBoneQuaternion(FName("calf_r")).Rotator();
	//포즈 체크
	float tolerance = 30.0f;
	if (FMath::IsNearlyEqual(upperarm_l.Pitch, -3.8f, tolerance) &&
		FMath::IsNearlyEqual(upperarm_l.Yaw, 1.8f, tolerance) &&
		FMath::IsNearlyEqual(upperarm_l.Roll, -95.0f, tolerance) &&
		FMath::IsNearlyEqual(lowerarm_l.Pitch, 22.0f, tolerance) &&
		FMath::IsNearlyEqual(lowerarm_l.Yaw, -10.0f, tolerance) &&
		FMath::IsNearlyEqual(lowerarm_l.Roll, -106.0f, tolerance) &&
		FMath::IsNearlyEqual(upperarm_r.Pitch, 10.6f, tolerance) &&
		FMath::IsNearlyEqual(upperarm_r.Yaw, -8.6f, tolerance) &&
		FMath::IsNearlyEqual(upperarm_r.Roll, 86.0f, tolerance) &&
		FMath::IsNearlyEqual(lowerarm_r.Pitch, -1.1f, tolerance) &&
		FMath::IsNearlyEqual(lowerarm_r.Yaw, 1.6f, tolerance) &&
		FMath::IsNearlyEqual(lowerarm_r.Roll, 90.3f, tolerance) &&

		FMath::IsNearlyEqual(thigh_l.Pitch, 7.1f, tolerance) &&
		FMath::IsNearlyEqual(thigh_l.Yaw, -89.1f, tolerance) &&
		FMath::IsNearlyEqual(thigh_l.Roll, -73.5f, tolerance) &&
		FMath::IsNearlyEqual(calf_l.Pitch, 15.3f, tolerance) &&
		FMath::IsNearlyEqual(calf_l.Yaw, -87.5f, tolerance) &&
		FMath::IsNearlyEqual(calf_l.Roll, -80.8f, tolerance) &&
		FMath::IsNearlyEqual(thigh_r.Pitch, -7.9f, tolerance) &&
		FMath::IsNearlyEqual(thigh_r.Yaw, 89.3f, tolerance) &&
		FMath::IsNearlyEqual(thigh_r.Roll, 98.1f, tolerance) &&
		FMath::IsNearlyEqual(calf_r.Pitch, -23.3f, tolerance) &&
		FMath::IsNearlyEqual(calf_r.Yaw, 88.5f, tolerance) &&
		FMath::IsNearlyEqual(calf_r.Roll, 98.0f, tolerance))
	{
		PoseCheck = true;
	}


	if (PoseCheck && MainGM->TrackedSkeleton_Num == 1 && Percent < 100)
	{
		ClientMainPC->DeltaRotation = true;
		warning = false;
		Percent++;

		if (MediaPlayer->IsPaused())
		{
			MediaPlayer->Play();
		}
	}
	else if (!PoseCheck || MainGM->TrackedSkeleton_Num != 1 && !warning)
	{
		ClientMainPC->DeltaRotation = false;
		warning = true;
		UGameplayStatics::PlaySound2D(this, Warning_03);

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