// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_2_1.h"
#include "Widget/ClientWidget_2_2.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#define INITTIMER 180

bool UClientWidget_2_1::isFirst = true;
ServerWidgetIndex UClientWidget_2_1::Index = ServerWidgetIndex::ServerWidget_2_1;
SelectLevel UClientWidget_2_1::Level = SelectLevel::Low;
Select_Button UClientWidget_2_1::Button = Select_Button::None;


UClientWidget_2_1::UClientWidget_2_1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<USoundWave> Button14(TEXT("SoundWave'/Game/Sound/Widget/버튼음_14.버튼음_14'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button09(TEXT("SoundWave'/Game/Sound/Widget/버튼음_09.버튼음_09'"));

	Button_14 = Button14.Object;
	Button_09 = Button09.Object;
}

void UClientWidget_2_1::NativeConstruct()
{
	Super::NativeConstruct();

	loading = false;

	Image_Procedure_Index = 0;
	Image_Procedures.AddUnique(Image_Procedure_1);
	Image_Procedures.AddUnique(Image_Procedure_2);
	Image_Procedures.AddUnique(Image_Procedure_3);
	Image_Procedures.AddUnique(Image_Procedure_4);
	Image_Procedures.AddUnique(Image_Procedure_5);

	for (auto Image : Image_Procedures)
	{
		if(Image != Image_Procedure_1)
			Image->SetVisibility(ESlateVisibility::Collapsed);
	}

	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Button_left->OnClicked.AddDynamic(this, &UClientWidget_2_1::OnClick_Button_left);
	Button_right->OnClicked.AddDynamic(this, &UClientWidget_2_1::OnClick_Button_right);
	Button_Next->OnClicked.AddDynamic(this, &UClientWidget_2_1::OnClick_Button_Next);
	Button_Close->OnClicked.AddDynamic(this, &UClientWidget_2_1::OnClick_Button_Close);

	if (isFirst)
	{
		Button_Next->SetVisibility(ESlateVisibility::Visible);
		Button_Close->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		Button_Next->SetVisibility(ESlateVisibility::Collapsed);
		Button_Close->SetVisibility(ESlateVisibility::Visible);
	}

	UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("FirstZOrder")), 1.5f, false);
	//SetMediaPath_Background();

	InitTimer = 0;
	InitTimerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CheckInitTimer")), 1.0f, true);
}

void UClientWidget_2_1::NativeDestruct()
{
	//MediaPlayer->Close();
	UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
	this->ConditionalBeginDestroy();
}

void UClientWidget_2_1::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, FString::FromInt(InitTimer));
}

void UClientWidget_2_1::SetMediaPath_Background()
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

void UClientWidget_2_1::FirstZOrder()
{
	loading = true;
}

void UClientWidget_2_1::OnClick_Button_left()
{
	InitTimer = 0;
	if (loading)
	{
		UGameplayStatics::PlaySound2D(this, Button_14);
		MainPC->PreHelperImage();

		if (Image_Procedure_Index > 0)
			Image_Procedure_Index--;

		for (auto Image : Image_Procedures)
		{
			if (Image == Image_Procedures[Image_Procedure_Index])
			{
				Image->SetVisibility(ESlateVisibility::Visible);
			}
			else
				Image->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UClientWidget_2_1::OnClick_Button_right()
{
	InitTimer = 0;
	if (loading)
	{
		UGameplayStatics::PlaySound2D(this, Button_14);
		MainPC->NextHelperImage();

		if (Image_Procedure_Index < Image_Procedures.Num() - 1)
			Image_Procedure_Index++;

		for (auto Image : Image_Procedures)
		{
			if (Image == Image_Procedures[Image_Procedure_Index])
			{
				Image->SetVisibility(ESlateVisibility::Visible);
			}
			else
				Image->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}


void UClientWidget_2_1::OnClick_Button_Next()
{
	InitTimer = 0;
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_2);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	ClientWidget_2_2 = CreateWidget<UClientWidget_2_2>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_2_2]);

	if (IsValid(ClientWidget_2_2))
	{
		ClientWidget_2_2->AddToViewport();
	}
	isFirst = false;
}

void UClientWidget_2_1::OnClick_Button_Close()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_09);
	MainPC->ShowServerWidget(Index, Level, Button);

	this->SetVisibility(ESlateVisibility::Collapsed);
}

void UClientWidget_2_1::CheckInitTimer()
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