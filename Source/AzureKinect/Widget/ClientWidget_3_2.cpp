// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/ClientWidget_3_2.h"
#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#define INITTIMER 30

SelectLevel UClientWidget_3_2::Level = SelectLevel::Low;

UClientWidget_3_2::UClientWidget_3_2(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> Low_Title(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_122.Asset_122'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Low_1(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_106.Asset_106'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Low_2(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_105.Asset_105'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Low_3(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_104.Asset_104'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Low_4(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_103.Asset_103'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Low_5(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_102.Asset_102'"));
	if (!Low_Title.Succeeded() || !Low_1.Succeeded() || !Low_2.Succeeded() || !Low_3.Succeeded() || !Low_4.Succeeded() || !Low_5.Succeeded())
		UE_LOG(LogTemp, Error, TEXT("UClientWidget_3_2 Constructor Failed!!!!!!!!!!!!!!!!!!!!!"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> Middle_Title(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_134.Asset_134'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Middle_1(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_116.Asset_116'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Middle_2(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_115.Asset_115'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Middle_3(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_114.Asset_114'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Middle_4(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_113.Asset_113'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> Middle_5(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_112.Asset_112'"));
	if (!Middle_Title.Succeeded() || !Middle_1.Succeeded() || !Middle_2.Succeeded() || !Middle_3.Succeeded() || !Middle_4.Succeeded() ||! Middle_5.Succeeded())
		UE_LOG(LogTemp, Error, TEXT("UClientWidget_3_2 Constructor Failed!!!!!!!!!!!!!!!!!!!!!!"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> High_Title(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_133.Asset_133'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> High_1(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_111.Asset_111'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> High_2(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_110.Asset_110'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> High_3(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_109.Asset_109'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> High_4(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_108.Asset_108'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> High_5(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_107.Asset_107'"));
	if (!High_Title.Succeeded() || !High_1.Succeeded() || !High_2.Succeeded() || !High_3.Succeeded() || !High_4.Succeeded() || !High_5.Succeeded())
		UE_LOG(LogTemp, Error, TEXT("UClientWidget_3_2 Constructor Failed!!!!!!!!!!!!!!!!!!!!!!!"));
	
	static ConstructorHelpers::FObjectFinder<UTexture2D> LowToggle_1(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_121.Asset_121'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LowToggle_2(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_120.Asset_120'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LowToggle_3(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_119.Asset_119'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LowToggle_4(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_118.Asset_118'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LowToggle_5(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Low/Asset_117.Asset_117'"));
	if (!LowToggle_1.Succeeded() || !LowToggle_2.Succeeded() || !LowToggle_3.Succeeded() || !LowToggle_4.Succeeded() || !LowToggle_5.Succeeded())
		UE_LOG(LogTemp, Error, TEXT("UClientWidget_3_2 Constructor Failed!!!!!!!!!!!!!!!!!!!!!"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> MiddleToggle_1(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_132.Asset_132'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> MiddleToggle_2(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_131.Asset_131'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> MiddleToggle_3(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_130.Asset_130'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> MiddleToggle_4(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_129.Asset_129'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> MiddleToggle_5(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/Middle/Asset_128.Asset_128'"));
	if (!MiddleToggle_1.Succeeded() || !MiddleToggle_2.Succeeded() || !MiddleToggle_3.Succeeded() || !MiddleToggle_4.Succeeded() || !MiddleToggle_5.Succeeded())
		UE_LOG(LogTemp, Error, TEXT("UClientWidget_3_2 Constructor Failed!!!!!!!!!!!!!!!!!!!!!"));

	static ConstructorHelpers::FObjectFinder<UTexture2D> HighToggle_1(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_127.Asset_127'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HighToggle_2(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_126.Asset_126'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HighToggle_3(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_125.Asset_125'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HighToggle_4(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_124.Asset_124'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HighToggle_5(TEXT("Texture2D'/Game/Widget/Texture_new_/3_2/High/Asset_123.Asset_123'"));
	if (!HighToggle_1.Succeeded() || !HighToggle_2.Succeeded() || !HighToggle_3.Succeeded() || !HighToggle_4.Succeeded() || !HighToggle_5.Succeeded())
		UE_LOG(LogTemp, Error, TEXT("UClientWidget_3_2 Constructor Failed!!!!!!!!!!!!!!!!!!!!!"));

	ButtonTextures.Init(NULL, 6);
	ButtonTextures_Toggle.Init(NULL, 5);

	if (Level == SelectLevel::Low)
	{
		ButtonTextures[0] = Low_Title.Object;
		ButtonTextures[1] = Low_1.Object;
		ButtonTextures[2] = Low_2.Object;
		ButtonTextures[3] = Low_3.Object;
		ButtonTextures[4] = Low_4.Object;
		ButtonTextures[5] = Low_5.Object;
		ButtonTextures_Toggle[0] = LowToggle_1.Object;
		ButtonTextures_Toggle[1] = LowToggle_2.Object;
		ButtonTextures_Toggle[2] = LowToggle_3.Object;
		ButtonTextures_Toggle[3] = LowToggle_4.Object;
		ButtonTextures_Toggle[4] = LowToggle_5.Object;
	}
	else if (Level == SelectLevel::Middle)
	{
		ButtonTextures[0] = Middle_Title.Object;
		ButtonTextures[1] = Middle_1.Object;
		ButtonTextures[2] = Middle_2.Object;
		ButtonTextures[3] = Middle_3.Object;
		ButtonTextures[4] = Middle_4.Object;
		ButtonTextures[5] = Middle_5.Object;
		ButtonTextures_Toggle[0] = MiddleToggle_1.Object;
		ButtonTextures_Toggle[1] = MiddleToggle_2.Object;
		ButtonTextures_Toggle[2] = MiddleToggle_3.Object;
		ButtonTextures_Toggle[3] = MiddleToggle_4.Object;
		ButtonTextures_Toggle[4] = MiddleToggle_5.Object;
	}
	else if (Level == SelectLevel::High)
	{
		ButtonTextures[0] = High_Title.Object;
		ButtonTextures[1] = High_1.Object;
		ButtonTextures[2] = High_2.Object;
		ButtonTextures[3] = High_3.Object;
		ButtonTextures[4] = High_4.Object;
		ButtonTextures[5] = High_5.Object;
		ButtonTextures_Toggle[0] = HighToggle_1.Object;
		ButtonTextures_Toggle[1] = HighToggle_2.Object;
		ButtonTextures_Toggle[2] = HighToggle_3.Object;
		ButtonTextures_Toggle[3] = HighToggle_4.Object;
		ButtonTextures_Toggle[4] = HighToggle_5.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundWave> Button14(TEXT("SoundWave'/Game/Sound/Widget/버튼음_11.버튼음_11'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> Button09(TEXT("SoundWave'/Game/Sound/Widget/버튼음_09.버튼음_09'"));

	Button_11 = Button14.Object;
	Button_09 = Button09.Object;
}

void UClientWidget_3_2::NativeConstruct()
{
	InitTimer = 0;
	InitTimerhandle = UKismetSystemLibrary::K2_SetTimer(this, FString(TEXT("CheckInitTimer")), 1.0f, true);

	MainPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	Button_1->OnClicked.AddDynamic(this, &UClientWidget_3_2::OnClick_Button_1);
	Button_2->OnClicked.AddDynamic(this, &UClientWidget_3_2::OnClick_Button_2);
	Button_3->OnClicked.AddDynamic(this, &UClientWidget_3_2::OnClick_Button_3);
	Button_4->OnClicked.AddDynamic(this, &UClientWidget_3_2::OnClick_Button_4);
	Button_5->OnClicked.AddDynamic(this, &UClientWidget_3_2::OnClick_Button_5);
	Button_Helper->OnClicked.AddDynamic(this, &UClientWidget_3_2::OnClick_Button_Helper);
	Button_Back->OnClicked.AddDynamic(this, &UClientWidget_3_2::OnClick_Button_Back);

	SetButtonTexture();
	
	//SetMediaPath_Background();
}

void UClientWidget_3_2::NativeDestruct()
{
	//MediaPlayer->Close();
	UKismetSystemLibrary::K2_ClearTimerHandle(this, InitTimerhandle);
	this->ConditionalBeginDestroy();
}

void UClientWidget_3_2::SetMediaPath_Background()
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

void UClientWidget_3_2::SetButtonTexture()
{
	Image_Level->SetBrushFromTexture(ButtonTextures[0]);

	FButtonStyle buttonstyle;
	FSlateBrush slatebrush;
	FSlateBrush slatebrush_Toggle;

	slatebrush.SetResourceObject(ButtonTextures[1]);
	slatebrush_Toggle.SetResourceObject(ButtonTextures_Toggle[0]);
	buttonstyle.SetNormal(slatebrush);
	buttonstyle.SetHovered(slatebrush);
	buttonstyle.SetPressed(slatebrush_Toggle);
	Button_1->SetStyle(buttonstyle);

	slatebrush.SetResourceObject(ButtonTextures[2]);
	slatebrush_Toggle.SetResourceObject(ButtonTextures_Toggle[1]);
	buttonstyle.SetNormal(slatebrush);
	buttonstyle.SetHovered(slatebrush);
	buttonstyle.SetPressed(slatebrush_Toggle);
	Button_2->SetStyle(buttonstyle);

	slatebrush.SetResourceObject(ButtonTextures[3]);
	slatebrush_Toggle.SetResourceObject(ButtonTextures_Toggle[2]);
	buttonstyle.SetNormal(slatebrush);
	buttonstyle.SetHovered(slatebrush);
	buttonstyle.SetPressed(slatebrush_Toggle);
	Button_3->SetStyle(buttonstyle);

	slatebrush.SetResourceObject(ButtonTextures[4]);
	slatebrush_Toggle.SetResourceObject(ButtonTextures_Toggle[3]);
	buttonstyle.SetNormal(slatebrush);
	buttonstyle.SetHovered(slatebrush);
	buttonstyle.SetPressed(slatebrush_Toggle);
	Button_4->SetStyle(buttonstyle);

	slatebrush.SetResourceObject(ButtonTextures[5]);
	slatebrush_Toggle.SetResourceObject(ButtonTextures_Toggle[4]);
	buttonstyle.SetNormal(slatebrush);
	buttonstyle.SetHovered(slatebrush);
	buttonstyle.SetPressed(slatebrush_Toggle);
	Button_5->SetStyle(buttonstyle);
}

void UClientWidget_3_2::OnClick_Button_1()
{
	InitTimer = 0;

	UGameplayStatics::PlaySound2D(this, Button_11);

	MainPC->SetMediaPath(Level, Select_Button::Button_1);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_3, Level, Select_Button::Button_1);

	UClientWidget_3_3::Level = Level;
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget = CreateWidget<UClientWidget_3_3>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_3_3]);

	if (IsValid(ClientWidget))
	{
		ClientWidget->AddToViewport();
	}
}

void UClientWidget_3_2::OnClick_Button_2()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	MainPC->SetMediaPath(Level, Select_Button::Button_2);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_3, Level, Select_Button::Button_2);

	UClientWidget_3_3::Level = Level;
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget = CreateWidget<UClientWidget_3_3>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_3_3]);

	if (IsValid(ClientWidget))
	{
		ClientWidget->AddToViewport();
	}
}

void UClientWidget_3_2::OnClick_Button_3()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	MainPC->SetMediaPath(Level, Select_Button::Button_3);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_3, Level, Select_Button::Button_3);

	UClientWidget_3_3::Level = Level;
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget = CreateWidget<UClientWidget_3_3>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_3_3]);

	if (IsValid(ClientWidget))
	{
		ClientWidget->AddToViewport();
	}
}

void UClientWidget_3_2::OnClick_Button_4()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	MainPC->SetMediaPath(Level, Select_Button::Button_4);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_3, Level, Select_Button::Button_4);

	UClientWidget_3_3::Level = Level;
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget = CreateWidget<UClientWidget_3_3>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_3_3]);

	if (IsValid(ClientWidget))
	{
		ClientWidget->AddToViewport();
	}
}

void UClientWidget_3_2::OnClick_Button_5()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	MainPC->SetMediaPath(Level, Select_Button::Button_5);

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_3, Level, Select_Button::Button_5);

	UClientWidget_3_3::Level = Level;
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto ClientWidget = CreateWidget<UClientWidget_3_3>(MainPC, MainPC->ClientWidgetClass[ServerWidgetIndex::ServerWidget_3_3]);

	if (IsValid(ClientWidget))
	{
		ClientWidget->AddToViewport();
	}
}


void UClientWidget_3_2::OnClick_Button_Helper()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_09);

	UClientWidget_2_1::Level = Level;
	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_2_1]);
	temp->AddToViewport();

	UClientWidget_2_1::Index = ServerWidgetIndex::ServerWidget_3_2;
	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_2_1);
}


void UClientWidget_3_2::OnClick_Button_Back()
{
	InitTimer = 0;
	UGameplayStatics::PlaySound2D(this, Button_11);

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	auto temp = CreateWidget(MainPC, MainPC->ClientWidgetClass[ClientWidgetIndex::ClientWidget_3_1]);
	temp->AddToViewport();

	MainPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_1, Level);
}

void UClientWidget_3_2::CheckInitTimer()
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