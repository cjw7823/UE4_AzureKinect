// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ServerWidget_3_3.h"
#include "Kismet/GameplayStatics.h"
#include "GuideGirlAnimInstance.h"

SelectLevel UServerWidget_3_3::Level = SelectLevel::Low;
Select_Button UServerWidget_3_3::Button = Select_Button::None;

UServerWidget_3_3::UServerWidget_3_3(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Low01(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Low/Asset_146.Asset_146'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Low02(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Low/Asset_151.Asset_151'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Low03(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Low/Asset_154.Asset_154'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Low04(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Low/Asset_157.Asset_157'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Low05(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Low/Asset_160.Asset_160'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Middle01(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Middle/Asset_5.Asset_5'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Middle02(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Middle/Asset_9.Asset_9'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Middle03(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Middle/Asset_12.Asset_12'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Middle04(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Middle/Asset_15.Asset_15'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_Middle05(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Middle/Asset_18.Asset_18'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_High01(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/High/Asset_163.Asset_163'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_High02(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/High/Asset_167.Asset_167'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_High03(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/High/Asset_170.Asset_170'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_High04(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/High/Asset_173.Asset_173'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Title_High05(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/High/Asset_176.Asset_176'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Explanation_Low(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Low/Asset_20.Asset_20'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Explanation_Middle(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/Middle/Asset_6.Asset_6'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Explanation_High(TEXT("Texture2D'/Game/Widget/Texture_new_/3_3/High/Asset_19.Asset_19'"));

	TitleTextures.AddUnique(Title_Low01.Object);
	TitleTextures.AddUnique(Title_Low02.Object);
	TitleTextures.AddUnique(Title_Low03.Object);
	TitleTextures.AddUnique(Title_Low04.Object);
	TitleTextures.AddUnique(Title_Low05.Object);

	TitleTextures.AddUnique(Title_Middle01.Object);
	TitleTextures.AddUnique(Title_Middle02.Object);
	TitleTextures.AddUnique(Title_Middle03.Object);
	TitleTextures.AddUnique(Title_Middle04.Object);
	TitleTextures.AddUnique(Title_Middle05.Object);

	TitleTextures.AddUnique(Title_High01.Object);
	TitleTextures.AddUnique(Title_High02.Object);
	TitleTextures.AddUnique(Title_High03.Object);
	TitleTextures.AddUnique(Title_High04.Object);
	TitleTextures.AddUnique(Title_High05.Object);
	
	Explanation.AddUnique(Explanation_Low.Object);
	Explanation.AddUnique(Explanation_Middle.Object);
	Explanation.AddUnique(Explanation_High.Object);

	static ConstructorHelpers::FClassFinder<AActor> BP_AnimMannequin(TEXT("Blueprint'/Game/Blueprints/BP_GuideGirl.BP_GuideGirl_C'"));
	GuideGirl = UGameplayStatics::GetActorOfClass(GetWorld(), BP_AnimMannequin.Class);

	static ConstructorHelpers::FObjectFinder<USoundWave> Back01(TEXT("SoundWave'/Game/Sound/Widget/배경음_01.배경음_01'"));

	Back_01 = Back01.Object;

	static ConstructorHelpers::FClassFinder<AActor> ActorBGM(TEXT("Blueprint'/Game/Blueprints/BGM_01.BGM_01_C'"));
	Audio01 = UGameplayStatics::GetActorOfClass(GetWorld(), ActorBGM.Class);
}

void UServerWidget_3_3::NativeConstruct()
{
	Super::NativeConstruct();
	//Audio01 = UGameplayStatics::SpawnSound2D(this, Back_01);

	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	auto temp = Cast<UGuideGirlAnimInstance>(anim);
	temp->WidgetIndex = WidgetIndex::ServerWidget_3_3;
	temp->ButtonIndex = (ButtonIndex)(uint8)Button;
	temp->CoachingLevel = (CoachingLevel)(uint8)Level;

	//SetMediaPath_Background();

	SetContents();

}

void UServerWidget_3_3::NativeDestruct()
{
	auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	if (Cast<UGuideGirlAnimInstance>(anim)->AudioCom != NULL)
	{
		Cast<UGuideGirlAnimInstance>(anim)->AudioCom->Stop();
	}

	/*if (Audio01 != NULL)
		Audio01->Stop();*/

	Cast<UAudioComponent>(Audio01->GetComponentByClass(UAudioComponent::StaticClass()))->Stop();

	//MediaPlayer->Close();

	this->ConditionalBeginDestroy();

	/*auto anim = Cast<USkeletalMeshComponent>(GuideGirl->GetComponentByClass(USkeletalMeshComponent::StaticClass()))->GetAnimInstance();
	auto temp = Cast<UGuideGirlAnimInstance>(anim);

	temp->ButtonIndex = ButtonIndex::None;
	temp->CoachingLevel = CoachingLevel::Level_None;
	temp->WidgetIndex = WidgetIndex::None;*/

	//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, TEXT("Native Destruct"));
}

void UServerWidget_3_3::SetMediaPath_Background()
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

void UServerWidget_3_3::SetContents()
{
	if (Level == SelectLevel::Low)
	{
		Image_Explanation->SetBrushFromTexture(Explanation[SelectLevel::Low]);
		if (Button == Select_Button::Button_1)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[0]);
			TextBlock_Name->SetText(FText::FromString(TEXT("인체(양사위), 좌우수선거사위와 세전디딤세,퇴세전디딤세 동작")));
			TextBlock_Explanation->SetText(FText::FromString(TEXT("팔을 앞 뒤로 감은 후 양팔을 곧게 뻗고 한걸음 씩 \n 발 디딤 하는 동작이에요")));
		}
		else if (Button == Select_Button::Button_2)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[1]);
			TextBlock_Name->SetText(FText::FromString(TEXT("양사위와 디딤세동작")));
			TextBlock_Explanation->SetText(FText::FromString(TEXT("팔을 앞 뒤로 감으며 한걸음 씩 발 디딤 하는 동작이에요")));
		}
		else if (Button == Select_Button::Button_3)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[2]);
			TextBlock_Name->SetText(FText::FromString(TEXT("평사위,만세사위와 디딤세동작")));
			TextBlock_Explanation->SetText(FText::FromString(TEXT("양 팔을 옆으로 뻗고 손 바닥을 번갈아 뒤집으며\n 발 디딤하는 동작이에요")));
		}
		else if (Button == Select_Button::Button_4)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[3]);
			TextBlock_Name->SetText(FText::FromString(TEXT("몸 감기사위와 디딤세동작")));
			TextBlock_Explanation->SetText(FText::FromString(TEXT("한 손은 머리 위로 들어 뒤집고 나머지 손은 허리를\n 크게 휘감으며 발 디딤하는 동작이에요")));
		}
		else if (Button == Select_Button::Button_5)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[4]);
			TextBlock_Name->SetText(FText::FromString(TEXT("사선사위와 디딤세동작")));
			TextBlock_Explanation->SetText(FText::FromString(TEXT("양 팔을 사선으로 들어 발 디딤하는 동작이에요")));
		}
	}
	else if (Level == SelectLevel::Middle)
	{
		Image_Explanation->SetBrushFromTexture(Explanation[SelectLevel::Middle]);
		if (Button == Select_Button::Button_1)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[5]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("만세사위과 굴신동작"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("양 팔을 만세 자세로 든 후 디딤과 굴신하는 동작이에요"))));
		}
		else if (Button == Select_Button::Button_2)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[6]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("머리감기사위와 굴신동작"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("양 팔을, 일직선으로 올린 뒤, 한 팔 씩 머리를\n 쓸어내리며, 굴신을 하는 동작이에요"))));
		}
		else if (Button == Select_Button::Button_3)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[7]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("좌우수선거사위,머리감기사위와 까치체"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("양 팔을 든 동작과 머리를 쓸어 내리는 동작을\n 각각하며 까치체를 하는동작이에요"))));
		}
		else if (Button == Select_Button::Button_4)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[8]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("머리감기사위와 발바치동작"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("한 팔씩 머리를 쓸어내리며 발을 무릎 위로\n 올리는 동작이에요"))));
		}
		else if (Button == Select_Button::Button_5)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[9]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("만세사위와 발바치동작"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("양 팔을 만세 자세로 올리며 발을 무릎 위로\n 올리는 동작이에요"))));
		}
	}
	else if (Level == SelectLevel::High)
	{
		Image_Explanation->SetBrushFromTexture(Explanation[SelectLevel::High]);
		if (Button == Select_Button::Button_1)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[10]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("좌우수선거사위,만세사위,머리감기사위와 도는동작"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("팔 사위를 하며 옆으로 발을 딛고 도는 동작이에요"))));
		}
		else if (Button == Select_Button::Button_2)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[11]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("양손감기사위와 도는동작"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("양 손을 들고 앞 뒤로 뒤집는 동작을 하며\n 발을 딛고 도는 동작이에요"))));
		}
		else if (Button == Select_Button::Button_3)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[12]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("만세사위와 도는동작"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("양팔을 만세 자세로 올리고 내리면서\n 딛고 도는 동작이에요"))));
		}
		else if (Button == Select_Button::Button_4)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[13]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("꽃 봉오리사위와 구슬돌이동작"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("양손 등을 마주보게 올리고 내리면서\n 딛고 도는 동작이에요"))));
		}
		else if (Button == Select_Button::Button_5)
		{
			Image_Title->SetBrushFromTexture(TitleTextures[14]);
			TextBlock_Name->SetText(FText::FromString(FString(TEXT("머리감기사위와 딛고 짚고 뛰는 동작"))));
			TextBlock_Explanation->SetText(FText::FromString(FString(TEXT("양 팔을 일직 선이 되도록 팔을 올린 후 한팔 씩 올려내리면서\n 옆으로 짚고 뛰고 앉는 동작이에요"))));
		}
	}
}
