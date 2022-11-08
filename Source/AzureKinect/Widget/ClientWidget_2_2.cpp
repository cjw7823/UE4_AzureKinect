// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_2_2.h"
#include "Widget/listitem.h"
#include "Widget/ClientWidget_2_3.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#define INITTIMER 180

UClientWidget_2_2::UClientWidget_2_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> Button14(TEXT("SoundWave'/Game/Sound/Widget/버튼음_14.버튼음_14'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button04(TEXT("SoundWave'/Game/Sound/Widget/버튼음_04.버튼음_04'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button10(TEXT("SoundWave'/Game/Sound/Widget/버튼음_10.버튼음_10'"));

	Button_14 = Button14.Object;
	Button_04 = Button04.Object;
	Button_10 = Button10.Object;
}

void UClientWidget_2_2::NativeConstruct()
{
	Super::NativeConstruct();

	InitTimer = 0;
	InitTimerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CheckInitTimer")), 1.0f, true);

	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Finish_Input_Hight = false;
	Finish_Input_Sex = false;
	Button_Finish->SetVisibility(ESlateVisibility::Collapsed);

	ListView_Hight->OnItemClicked().AddUObject(this, &UClientWidget_2_2::Hight_Click);
	ListView_Sex->OnItemClicked().AddUObject(this, &UClientWidget_2_2::Sex_Click);
	ListView_Hight->OnListViewScrolled().AddUObject(this, &UClientWidget_2_2::Sync_ListView);

	Button_Finish->OnClicked.AddDynamic(this, &UClientWidget_2_2::OnClick_Button_Next);
	Button_Sex->OnPressed.AddDynamic(this, &UClientWidget_2_2::OnPressed_Button_Sex);
	Button_Hight->OnPressed.AddDynamic(this, &UClientWidget_2_2::OnPressed_Button_Hight);
	Button_Sex->OnReleased.AddDynamic(this, &UClientWidget_2_2::OnReleased_Button);
	Button_Hight->OnReleased.AddDynamic(this, &UClientWidget_2_2::OnReleased_Button);

	for (int i = 140; i <= 190; i+=5)
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

void UClientWidget_2_2::NativeDestruct()
{
	//MediaPlayer->Close();
	UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
	this->ConditionalBeginDestroy();
}

void UClientWidget_2_2::Hight_Click(UObject* obj)
{
	InitTimer = 0;

	UGameplayStatics::PlaySound2D(this, Button_10);
	Finish_Input_Hight = true;
	if (Finish_Input_Hight && Finish_Input_Sex && !Button_Finish->IsVisible())
	{
		Button_Finish->SetVisibility(ESlateVisibility::Visible);
	}
	Ulistitem* temp = Cast<Ulistitem>(obj);

	int32 index = ListView_Hight->GetIndexForItem(obj);

	MainPC->SetUserData_Hight(temp->hight, index);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, FString::Printf(TEXT("Hight item : %d"), temp->hight));

}

void UClientWidget_2_2::Sex_Click(UObject* obj)
{
	InitTimer = 0;

	UGameplayStatics::PlaySound2D(this, Button_10);
	Finish_Input_Sex = true;
	if (Finish_Input_Hight && Finish_Input_Sex && !Button_Finish->IsVisible())
	{
		Button_Finish->SetVisibility(ESlateVisibility::Visible);
	}
	Ulistitem* temp = Cast<Ulistitem>(obj);

	int32 index = ListView_Sex->GetIndexForItem(obj);

	MainPC->SetUserData_Sex(temp->sex, index);

	if (temp->sex == FString(TEXT("남자")))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, FString::Printf(TEXT("Sex item : %s"), TEXT("남자")));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Yellow, FString::Printf(TEXT("Sex item : %s"), TEXT("여자")));
}


void UClientWidget_2_2::Sync_ListView(float a, float b)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("%f, %f"), a,b));
	MainPC->Sync_ListView(a);
}

void UClientWidget_2_2::SetMediaPath_Background()
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

void UClientWidget_2_2::OnClick_Button_Next()
{
	InitTimer = 0;

	UGameplayStatics::PlaySound2D(this, Button_14);
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_3);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	ClientWidget_2_3 = CreateWidget<UClientWidget_2_3>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_2_3]);

	if (IsValid(ClientWidget_2_3))
	{
		ClientWidget_2_3->AddToViewport();
	}
}

void UClientWidget_2_2::OnPressed_Button_Sex()
{
	InitTimer = 0;

	UGameplayStatics::PlaySound2D(this, Button_04);
	Image_Sex->SetVisibility(ESlateVisibility::Visible);
	ListView_Sex->SetVisibility(ESlateVisibility::Visible);
	bar->SetVisibility(ESlateVisibility::Visible);

	MainPC->ClickButton_2_2_Pressed(FString(TEXT("Sex")));
}

void UClientWidget_2_2::OnPressed_Button_Hight()
{
	InitTimer = 0;

	UGameplayStatics::PlaySound2D(this, Button_04);
	Image_Hight->SetVisibility(ESlateVisibility::Visible);
	ListView_Hight->SetVisibility(ESlateVisibility::Visible);

	MainPC->ClickButton_2_2_Pressed(FString(TEXT("Hight")));
}

void UClientWidget_2_2::OnReleased_Button()
{
	InitTimer = 0;

	MainPC->ClickButton_2_2_Released();
}

void UClientWidget_2_2::CheckInitTimer()
{
	InitTimer += 1;

	if (InitTimer >= INITTIMER)
	{
		UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
		UClientWidget_1_1::isFirst = true;
		UClientWidget_2_1::isFirst = true;

		MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_1_1);
		UWidgetLayoutLibrary::RemoveAllWidgets(this);
		auto temp = CreateWidget<UClientWidget_1_1>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_1_1]);

		if (IsValid(temp))
		{
			temp->AddToViewport();
		}
	}
}

#undef INITTIMER