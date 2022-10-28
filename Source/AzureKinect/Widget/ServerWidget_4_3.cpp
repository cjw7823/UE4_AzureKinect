// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ServerWidget_4_3.h"
#include "MainPlayerController.h"
#include "AzureKinectManager.h"
#include "Widget/Pictogram.h"

#define FILENAME "User_Data.json"

FString JsonStr;
TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<>::Create(&JsonStr);

UServerWidget_4_3::UServerWidget_4_3(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UMaterial> UserMaterial(TEXT("Material'/Game/Widget/M_User_RenderTarget2D.M_User_RenderTarget2D'"));
	User_Material = UserMaterial.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> Button04(TEXT("SoundWave'/Game/Sound/Widget/버튼음_04.버튼음_04'"));
	Button_04 = Button04.Object;

	static ConstructorHelpers::FClassFinder<AActor> BP_User_Doll(TEXT("Blueprint'/Game/Blueprints/BP_User_Doll.BP_User_Doll_C'"));
	Doll = BP_User_Doll.Class;
}

void UServerWidget_4_3::NativeConstruct()
{
	Super::NativeConstruct();

	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	UActorComponent* temp = UGameplayStatics::GetActorOfClass(GetWorld(), Doll)->GetComponentByClass(USkeletalMeshComponent::StaticClass());
	Anim_UserDoll = Cast<UAnim_UserDoll>(Cast<USkeletalMeshComponent>(temp)->GetAnimInstance());

	JsonStr = FString();

	Writer = TJsonWriterFactory<>::Create(&JsonStr);
	Writer->WriteObjectStart();

	is_OpenResource = false;
	is_Play = false;
	FrameNum = 0;
	Count = 3;
	once = true;
	Image_Coaching->SetVisibility(ESlateVisibility::Collapsed);
	Image_Coaching_Side->SetVisibility(ESlateVisibility::Collapsed);
	Image_User->SetVisibility(ESlateVisibility::Collapsed);
	Image_Indexmap->SetVisibility(ESlateVisibility::Collapsed);
	Pictogram_0->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_Count->SetVisibility(ESlateVisibility::Visible);

	//TextBlock_Count->TextDelegate.BindDynamic(this, &UServerWidget_4_3::Textbinding);

	SetCoachingVideo();
	SetCoachingVideo_Side();
	SetUserVideo();

	FilePath = FPaths::ProjectDir() + TEXT("UserData/") + TEXT(FILENAME);

	timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CountDown")), 1.0f, false);

	Cast<UPictogram>(Pictogram_0)->MediaPlayer = MediaPlayer;
}

void UServerWidget_4_3::NativeDestruct()
{
	UKismetSystemLibrary::K2_ClearTimerHandle(GetWorld(), timerhandle);

	MediaPlayer->Close();
	MediaPlayer_Side->Close();

	//Pictogram_0->ConditionalBeginDestroy();
	this->ConditionalBeginDestroy();
}

void UServerWidget_4_3::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (is_Play)
	{
		Save_to_Jsonfile();
	}
}

void UServerWidget_4_3::CountDown()
{
	if (Count > 0)
	{
		UGameplayStatics::PlaySound2D(this, Button_04);
		Count--;
	}

	if (Count <= 0 && is_OpenResource)
	{
		Image_Coaching->SetVisibility(ESlateVisibility::Visible);
		Image_Coaching_Side->SetVisibility(ESlateVisibility::Visible);
		Image_User->SetVisibility(ESlateVisibility::Visible);
		Image_Indexmap->SetVisibility(ESlateVisibility::Visible);
		Pictogram_0->SetVisibility(ESlateVisibility::Visible);
		TextBlock_Count->SetVisibility(ESlateVisibility::Collapsed);

		MediaPlayer->Play();
		MediaPlayer_Side->Play();
	}
	else if (Count <= 0 && !is_OpenResource)
	{
		timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CountDown")), 0.1f, false);
	}
	else
	{
		timerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CountDown")), 1.0f, false);
	}
}

//FText UServerWidget_4_3::Textbinding()
//{
//	FString temp;
//	temp = FString::FromInt(Count);
//	return FText::FromString(temp);
//}


void UServerWidget_4_3::SetCoachingVideo()
{
	MediaTexture = NewObject<UMediaTexture>(this);
	FileMediaSource = NewObject<UFileMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);

	MediaPlayer->OnMediaOpened.AddDynamic(this, &UServerWidget_4_3::CheckOpenResource);
	MediaPlayer->OnMediaOpenFailed.AddDynamic(this, &UServerWidget_4_3::FailOpenResource);
	MediaPlayer->OnEndReached.AddDynamic(this, &UServerWidget_4_3::EndPlay);
	MediaPlayer->OnPlaybackSuspended.AddDynamic(this, &UServerWidget_4_3::PlaybackSuspended);
	MediaPlayer->OnPlaybackResumed.AddDynamic(this, &UServerWidget_4_3::PlaybackResumed);

	FileMediaSource->SetFilePath(MainPC->MediaPath);
	MediaPlayer->PlayOnOpen = false;
	MediaPlayer->OpenSource(FileMediaSource);
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();	
	Image_Coaching->SetBrushResourceObject(MediaTexture);
}

void UServerWidget_4_3::SetCoachingVideo_Side()
{
	MediaTexture_Side = NewObject<UMediaTexture>(this);
	FileMediaSource_Side = NewObject<UFileMediaSource>(this);
	MediaPlayer_Side = NewObject<UMediaPlayer>(this);

	FileMediaSource_Side->SetFilePath(MainPC->MediaPath_Side);
	MediaPlayer_Side->PlayOnOpen = false;
	MediaPlayer_Side->OpenSource(FileMediaSource_Side);
	MediaTexture_Side->SetMediaPlayer(MediaPlayer_Side);
	MediaTexture_Side->UpdateResource();
	Image_Coaching_Side->SetBrushResourceObject(MediaTexture_Side);
}

void UServerWidget_4_3::SetUserVideo()
{
	Image_User->SetBrushFromMaterial(User_Material);
}

void UServerWidget_4_3::CheckOpenResource(FString OpenedUrl)
{
	is_OpenResource = true;
}

void UServerWidget_4_3::FailOpenResource(FString OpenedUrl)
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Fail"));
}

void UServerWidget_4_3::EndPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Playing Done."));

	is_Play = false;

	Writer->WriteValue(FString(TEXT("TOTAL_FRAME")), FrameNum);
	Writer->WriteObjectEnd();
	Writer->Close();

	FFileHelper::SaveStringToFile(*JsonStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), once);
	
	/*if (Jsonstr)
	{
		FFileHelper::SaveStringToFile(*JsonStr, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get());
	}*/

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_5_1);

	AMainPlayerController* Client_MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 1));
	Client_MainPC->ShowClientWidget(ClientWidgetIndex::ClientWidget_5_1);
}

void UServerWidget_4_3::PlaybackSuspended()
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Pause..."));
	if (MediaPlayer->IsBuffering())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("MediaPlayer Buffering..."));
	}
	if (MediaPlayer_Side->IsBuffering())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("MediaPlayer_Side Buffering..."));
	}
}

void UServerWidget_4_3::PlaybackResumed()
{
	is_Play = true;
}

void UServerWidget_4_3::Save_to_Jsonfile()
{
	FrameNum += 1;
	Writer->WriteObjectStart(FString::FromInt(FrameNum));

	//멀티 키넥스 사용 시, 최종 적용된 Rotation을 기록해야 하므로 폐지. 밑의 코드는 주석처리시 코드가 꼬임. 왜인지 알 수 없음...
	UAzureKinectManager::GetBodies(0);
	//auto Joints = temp[0]->GetJoints();

	/*const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EKinectBodyJointId"), true);

	for (auto joint : Joints)
	{
		if (CharStateEnum)
		{
			const FString EnumToName = CharStateEnum->GetNameStringByValue(joint.Index);
			Writer->WriteObjectStart(EnumToName);
			Writer->WriteValue(FString(TEXT("Pitch")), joint.Orientation.Pitch);
			Writer->WriteValue(FString(TEXT("Yaw")), joint.Orientation.Yaw);
			Writer->WriteValue(FString(TEXT("Roll")), joint.Orientation.Roll);
			Writer->WriteObjectEnd();
		}
	}*/

	auto Transform = Anim_UserDoll->JointsTransform_C;
	const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EKinectBodyJointId"), true);

	for (int i = 0; i < Transform.Num(); i++)
	{
		FRotator joint = Transform[i].GetRotation().Rotator();

		if (CharStateEnum)
		{
			const FString EnumToName = CharStateEnum->GetNameStringByValue(i);
			Writer->WriteObjectStart(EnumToName);
			Writer->WriteValue(FString(TEXT("Pitch")), joint.Pitch);
			Writer->WriteValue(FString(TEXT("Yaw")), joint.Yaw);
			Writer->WriteValue(FString(TEXT("Roll")), joint.Roll);
			Writer->WriteObjectEnd();
		}
	}

	Writer->WriteObjectEnd();
}

#undef FILENAME