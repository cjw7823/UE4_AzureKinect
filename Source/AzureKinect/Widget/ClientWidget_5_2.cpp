// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_5_2.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#define INITTIMER 180

UClientWidget_5_2::UClientWidget_5_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> PlayButton(TEXT("Texture2D'/Game/Widget/Texture_new_/5_2/Asset_202.Asset_202'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> PauseButton(TEXT("Texture2D'/Game/Widget/Texture_new_/5_2/Asset_207.Asset_207'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> PlayButton_Toggle(TEXT("Texture2D'/Game/Widget/Texture_new_/5_2/Asset_205.Asset_205'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> PauseButton_Toggle(TEXT("Texture2D'/Game/Widget/Texture_new_/5_2/Asset_206.Asset_206'"));

	Texture_play = PlayButton.Object;
	Texture_pause = PauseButton.Object;
	Texture_playToggle = PlayButton_Toggle.Object;
	Texture_pauseToggle = PauseButton_Toggle.Object;

	static ConstructorHelpers::FObjectFinder<USoundWave> Button14(TEXT("SoundWave'/Game/Sound/Widget/버튼음_14.버튼음_14'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button09(TEXT("SoundWave'/Game/Sound/Widget/버튼음_09.버튼음_09'"));

	Button_14 = Button14.Object;
	Button_09 = Button09.Object;
}

void UClientWidget_5_2::NativeConstruct()
{
	Super::NativeConstruct();

	InitTimer = 0;
	InitTimerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CheckInitTimer")), 1.0f, true);

	is_play = false;
	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Button_Back->OnClicked.AddDynamic(this, &UClientWidget_5_2::OnClick_Button_Back);
	Button_Slow->OnClicked.AddDynamic(this, &UClientWidget_5_2::OnClick_Button_Slow);
	Button_Play->OnClicked.AddDynamic(this, &UClientWidget_5_2::OnClick_Button_Play);
	Button_Fast->OnClicked.AddDynamic(this, &UClientWidget_5_2::OnClick_Button_Fast);
	Seeker->OnControllerCaptureBegin.AddDynamic(this, &UClientWidget_5_2::Test);
	Seeker->OnMouseCaptureBegin.AddDynamic(this, &UClientWidget_5_2::OnMouseCaptureBegin);
	Seeker->OnMouseCaptureEnd.AddDynamic(this, &UClientWidget_5_2::OnMouseCaptureEnd);

	SetPlayButtonTexture(Texture_play, Texture_playToggle);
	//SetMediaPath_Background();
}

void UClientWidget_5_2::NativeDestruct()
{
	//MediaPlayer->Close();
	UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
	this->ConditionalBeginDestroy();
}

void UClientWidget_5_2::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{

}

void UClientWidget_5_2::SetPlayButtonTexture(UTexture2D* texture, UTexture2D* texture_toggle)
{
	FButtonStyle buttonstyle;
	FSlateBrush slatebrush1;
	FSlateBrush slatebrush2;

	slatebrush1.SetResourceObject(texture);
	slatebrush2.SetResourceObject(texture_toggle);
	buttonstyle.SetNormal(slatebrush1);
	buttonstyle.SetHovered(slatebrush1);
	buttonstyle.SetPressed(slatebrush2);
	Button_Play->SetStyle(buttonstyle);
}

void UClientWidget_5_2::SetMediaPath_Background()
{
	MediaTexture = NewObject<UMediaTexture>(this);
	FileMediaSource = NewObject<UFileMediaSource>(this);
	MediaPlayer = NewObject<UMediaPlayer>(this);

	FileMediaSource->SetFilePath(FString(TEXT("./Movies/Widget/BG_wave.mp4")));
	MediaPlayer->OpenSource(FileMediaSource);
	MediaPlayer->SetLooping(true);
	MediaTexture->SetMediaPlayer(MediaPlayer);
	MediaTexture->UpdateResource();
	Image_Background->SetBrushResourceObject(MediaTexture);
}

void UClientWidget_5_2::OnClick_Button_Back()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_14);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_5_1);

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget = CreateWidget<UClientWidget_5_1>(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_5_1]);

	if (IsValid(ClientWidget))
	{
		ClientWidget->AddToViewport();
	}
}

void UClientWidget_5_2::OnClick_Button_Slow()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_14);

	if (!is_play)
	{
		is_play = !is_play;
	}
	MainPC->SetMediaPlayerRate(2);
	SetPlayButtonTexture(Texture_pause, Texture_pauseToggle);
}

void UClientWidget_5_2::OnClick_Button_Play()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_14);

	if (!is_play)
	{
		MainPC->SetMediaPlayerRate(1);
		SetPlayButtonTexture(Texture_pause, Texture_pauseToggle);
		is_play = true;
	}
	else
	{
		MainPC->SetMediaPlayerRate(0);
		SetPlayButtonTexture(Texture_play, Texture_playToggle);
		is_play = false;
	}
}

void UClientWidget_5_2::OnClick_Button_Fast()
{
	UE_LOG(LogTemp, Error, TEXT("helloC++"));
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_14);

	if (!is_play)
	{
		is_play = !is_play;
	}
	MainPC->SetMediaPlayerRate(3);
	SetPlayButtonTexture(Texture_pause, Texture_pauseToggle);
}

void UClientWidget_5_2::Test()
{
	GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, TEXT("OnControllerCaptureBegin"));
}

void UClientWidget_5_2::OnMouseCaptureBegin()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("OnMouseCaptureBegin"));
	if (is_play)
	{
		OnClick_Button_Play();
	}

}

void UClientWidget_5_2::OnMouseCaptureEnd()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("OnMouseCaptureEnd"));
	auto SeekValue = Seeker->GetValue();
	MainPC->SeekMediaPlayer(SeekValue);

	if (!is_play)
	{
		OnClick_Button_Play();
	}
	
	//Seek 후 자동 재생 기능은 서버에서 Seek이 실패 할 수 있으므로 보류.

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%f"), SeekValue));
}

void UClientWidget_5_2::CheckInitTimer()
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