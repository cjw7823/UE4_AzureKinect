// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ServerWidget_5_2.h"
#include "MainPlayerController.h"
#include "Replay_Mannequin.h"
#include "Misc/FileHelper.h"
#include "AzureKinectHelper.h"
#include "Kismet/KismetMathLibrary.h"
#include "GuideGirlAnimInstance.h"
#include "/work/ue4_azure_kinect/Source/AzureKinect/Widget/Referee.h"

#define FILENAME "User_Data.json"
#define INTERPORATION 15

UServerWidget_5_2::UServerWidget_5_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UMaterial> UserMaterial(TEXT("Material'/Game/Widget/M_Replay_RenderTarget2D.M_Replay_RenderTarget2D'"));
	User_Material = UserMaterial.Object;

	static ConstructorHelpers::FClassFinder<AActor> BP_AnimMannequin(TEXT("Blueprint'/Game/Blueprints/BP_GuideGirl.BP_GuideGirl_C'"));
	GuideGirl = UGameplayStatics::GetActorOfClass(GetWorld(), BP_AnimMannequin.Class);

	auto pc = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
	referee = pc->GetReferee();
}

void UServerWidget_5_2::NativeConstruct()
{
	Super::NativeConstruct();

	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ClientMainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 1));
	ReplayMannequin = Cast<AReplay_Mannequin>(UGameplayStatics::GetActorOfClass(GetWorld(), AReplay_Mannequin::StaticClass()));

	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	Cast<UGuideGirlAnimInstance>(anim)->WidgetIndex = WidgetIndex::ServerWidget_5_2;

	is_OpenResource = false;
	is_Play = false;
	Duration = 0;
	CurPerDu = 0;
	FrameNum = 0;
	preRotation.Init(FRotator(), 32);
	TextBlock_Rate->SetText(FText::FromString(FString("")));
	SetCoachingVideo();
	SetUserVideo();
	//SetMediaPath_Background();

	FilePath = FPaths::ProjectDir() + TEXT("UserData/") + TEXT(FILENAME);
	FFileHelper::LoadFileToString(Json_String, *FilePath);
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Json_String);
	jsonObj = MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(Reader, jsonObj);
	FrameNum = jsonObj->GetIntegerField(FString(TEXT("TOTAL_FRAME")));

	SetSkeletalTransform_FirstPose();

	//referee로 채점 후 채점 결과 넘기기
	CorrectFrame = referee->GetUserFrames();
}

void UServerWidget_5_2::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (Duration != 0 && is_Play)
	{
		auto CurTime = MediaPlayer->GetTime();
		if (CurTime != FTimespan::Zero())
		{
			CurPerDu = CurTime.GetTotalSeconds() / Duration;
			//Seeker->SetValue(CurPerDu);
			ClientMainPC->SyncMediaDuration(CurPerDu);
			//Seeker->OnValueChanged.Broadcast(CurPerDu);

			SetSkeletalTransform(InDeltaTime);
		}
	}
}

void UServerWidget_5_2::NativeDestruct()
{
	MediaPlayer->Close();
	//MediaPlayer_Background->Close();

	ReplayMannequin->SetMeshColor(-1, -1, -1, -1);

	this->ConditionalBeginDestroy();
}

void UServerWidget_5_2::SetCoachingVideo()
{
	MediaTexture = NewObject<UMediaTexture>(this);
	FileMediaSource = NewObject<UFileMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);
	MediaPlayer->OnMediaOpened.AddDynamic(this, &UServerWidget_5_2::CheckOpenResource);
	MediaPlayer->OnMediaOpenFailed.AddDynamic(this, &UServerWidget_5_2::FailOpenResource);
	MediaPlayer->OnEndReached.AddDynamic(this, &UServerWidget_5_2::EndPlay);
	MediaPlayer->OnPlaybackResumed.AddDynamic(this, &UServerWidget_5_2::OnPlaybackResumed);
	MediaPlayer->OnPlaybackSuspended.AddDynamic(this, &UServerWidget_5_2::PlaybackSuspended);
	//Seeker->OnValueChanged.AddDynamic(this, &UServerWidget_5_2::SyncMediaDuration);

	FileMediaSource->SetFilePath(MainPC->MediaPath);
	MediaPlayer->PlayOnOpen = false;
	MediaPlayer->SetLooping(true);
	MediaPlayer->OpenSource(FileMediaSource);
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Coaching->SetBrushResourceObject(MediaTexture);
}

void UServerWidget_5_2::SetUserVideo()
{
	Image_User->SetBrushFromMaterial(User_Material);
}

void UServerWidget_5_2::SetMediaPath_Background()
{
	MediaTexture_Background = NewObject<UMediaTexture>(this);
	FileMediaSource_Background = NewObject<UFileMediaSource>(this);
	MediaPlayer_Background = NewObject<UMediaPlayer>(this);

	FileMediaSource_Background->SetFilePath(FString(TEXT("./Movies/Widget/BG_wave.mp4")));
	MediaPlayer_Background->OpenSource(FileMediaSource_Background);
	MediaPlayer_Background->SetLooping(true);
	MediaTexture_Background->SetMediaPlayer(MediaPlayer_Background);
	MediaTexture_Background->UpdateResource();
	Image_Background->SetBrushResourceObject(MediaTexture_Background);
}

void UServerWidget_5_2::CheckOpenResource(FString OpenedUrl)
{
	is_OpenResource = true;

	Duration = MediaPlayer->GetDuration().GetTotalSeconds();
	//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, FString::Printf(TEXT("%f"), Duration));

}

void UServerWidget_5_2::FailOpenResource(FString OpenedUrl)
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail"));
}

void UServerWidget_5_2::EndPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("EndPlay"));

	ReplayMannequin->SetMeshColor(-1, -1, -1, -1);

}

void UServerWidget_5_2::PlaybackSuspended()
{
	//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Pause..."));
	is_Play = false;

	ReplayMannequin->SetMeshColor(-1, -1, -1, -1);
}

void UServerWidget_5_2::OnPlaybackResumed()
{
	is_Play = true;
}

void UServerWidget_5_2::SyncMediaDuration(float value)
{
	ClientMainPC->SyncMediaDuration(value);
}

void UServerWidget_5_2::SetSkeletalTransform(float InDeltaTime)
{
	const TSharedPtr<FJsonObject>* JsonObject;

	int32 Correction = 40;
	int32 Frame = (double)FrameNum * CurPerDu;
	//실수연산이기 때문에 몇개의 프레임은 씹힌다.
	//GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, FString::Printf(TEXT("%d"), Frame));
	
	if (jsonObj->TryGetObjectField(FString::FromInt(Frame + Correction), JsonObject))
	{
		const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EKinectBodyJointId"), true);
		for (uint8 i = 0; i < (uint8)EKinectBodyJointId::COUNT; i++)
		{
			const FString EnumToName = CharStateEnum->GetNameStringByValue(i);
			TSharedPtr<FJsonObject> EachJoint = (*JsonObject)->GetObjectField(EnumToName);
			float Pitch = EachJoint->GetNumberField(TEXT("Pitch"));
			float Yaw = EachJoint->GetNumberField(TEXT("Yaw"));
			float Roll = EachJoint->GetNumberField(TEXT("Roll"));

			FRotator temp = UKismetMathLibrary::RLerp(preRotation[i], FRotator(Pitch, Yaw, Roll), INTERPORATION * InDeltaTime, true);

			ReplayMannequin->SetReplayTransform(i, temp.Pitch, temp.Yaw, temp.Roll);
			//ReplayMannequin->SetReplayTransform(i, Pitch, Yaw, Roll);


			preRotation[i] = temp;
		}

		for (int j = 0; j < CorrectFrame.Num(); j++)
		{
			if (abs(Frame - CorrectFrame[j]) < 50)
			{
				//i번째의 채점값 가져오기.
				int32 la = referee->Getleftarm()[j];
				int32 ra = referee->Getrightarm()[j];
				int32 ll = referee->Getleftleg()[j];
				int32 rl = referee->Getrightleg()[j];

				//가져온 값으로 단지 메시의 색만 변경하는 함수. 점수 따위를 계산하지 않음.
				ReplayMannequin->SetMeshColor(la, ra, ll, rl);
				break;
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("Frame Parsing Falied"));
	}
}

void UServerWidget_5_2::SetSkeletalTransform_FirstPose()
{
	const TSharedPtr<FJsonObject>* JsonObject;
	int32 Frame = (int32)(FrameNum * CurPerDu);
	//실수연산이기 때문에 몇개의 프레임은 씹힌다.
	//GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, FString::Printf(TEXT("%d"), Frame));

	if (jsonObj->TryGetObjectField(FString::FromInt(1), JsonObject))
	{
		const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EKinectBodyJointId"), true);
		for (uint8 i = 0; i < (uint8)EKinectBodyJointId::COUNT; i++)
		{
			const FString EnumToName = CharStateEnum->GetNameStringByValue(i);
			TSharedPtr<FJsonObject> EachJoint = (*JsonObject)->GetObjectField(EnumToName);
			float Pitch = EachJoint->GetNumberField(TEXT("Pitch"));
			float Yaw = EachJoint->GetNumberField(TEXT("Yaw"));
			float Roll = EachJoint->GetNumberField(TEXT("Roll"));
			ReplayMannequin->SetReplayTransform(i, Pitch, Yaw, Roll);
			
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, TEXT("Frame Parsing Falied"));
	}
}
