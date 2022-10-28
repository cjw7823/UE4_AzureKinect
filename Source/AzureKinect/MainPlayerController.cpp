// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget/Referee.h"
#include "Widget/Pictogram.h"

Referee* AMainPlayerController::referee = NULL;

AMainPlayerController::AMainPlayerController()
{
	SetShowMouseCursor(true);

	referee = Referee::Create();

	//실패시 런타임 오류 발생.
	static ConstructorHelpers::FClassFinder<UServerWidget_1_1> S_WidgetClass_1_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_1_1.ServerWidget_1_1_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_1_1> C_WidgetClass_1_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_1_1.ClientWidget_1_1_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_2_1> S_WidgetClass_2_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_2_1.ServerWidget_2_1_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_2_1> C_WidgetClass_2_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_2_1.ClientWidget_2_1_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_2_2> S_WidgetClass_2_2(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_2_2.ServerWidget_2_2_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_2_2> C_WidgetClass_2_2(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_2_2.ClientWidget_2_2_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_2_3> S_WidgetClass_2_3(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_2_3.ServerWidget_2_3_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_2_3> C_WidgetClass_2_3(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_2_3.ClientWidget_2_3_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_3_1> S_WidgetClass_3_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_3_1.ServerWidget_3_1_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_3_1> C_WidgetClass_3_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_3_1.ClientWidget_3_1_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_3_2> S_WidgetClass_3_2(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_3_2.ServerWidget_3_2_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_3_2> C_WidgetClass_3_2(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_3_2.ClientWidget_3_2_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_3_3> S_WidgetClass_3_3(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_3_3.ServerWidget_3_3_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_3_3> C_WidgetClass_3_3(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_3_3.ClientWidget_3_3_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_4_1> S_WidgetClass_4_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_4_1.ServerWidget_4_1_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_4_1> C_WidgetClass_4_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_4_1.ClientWidget_4_1_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_4_2> S_WidgetClass_4_2(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_4_2.ServerWidget_4_2_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_4_2> C_WidgetClass_4_2(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_4_2.ClientWidget_4_2_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_4_3> S_WidgetClass_4_3(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_4_3.ServerWidget_4_3_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_4_3> C_WidgetClass_4_3(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_4_3.ClientWidget_4_3_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_5_1> S_WidgetClass_5_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_5_1.ServerWidget_5_1_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_5_1> C_WidgetClass_5_1(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_5_1.ClientWidget_5_1_C'"));
	static ConstructorHelpers::FClassFinder<UServerWidget_5_2> S_WidgetClass_5_2(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ServerWidget_5_2.ServerWidget_5_2_C'"));
	static ConstructorHelpers::FClassFinder<UClientWidget_5_2> C_WidgetClass_5_2(TEXT("WidgetBlueprint'/Game/Widget/Blueprints/ClientWidget_5_2.ClientWidget_5_2_C'"));

	if (!S_WidgetClass_1_1.Succeeded() || !C_WidgetClass_1_1.Succeeded() || !S_WidgetClass_2_1.Succeeded() || !C_WidgetClass_2_1.Succeeded() ||
		!S_WidgetClass_2_2.Succeeded() || !C_WidgetClass_2_2.Succeeded() || !S_WidgetClass_2_3.Succeeded() || !C_WidgetClass_2_3.Succeeded() ||
		!S_WidgetClass_3_1.Succeeded() || !C_WidgetClass_3_1.Succeeded() || !S_WidgetClass_3_2.Succeeded() || !C_WidgetClass_3_2.Succeeded() ||
		!S_WidgetClass_4_1.Succeeded() || !C_WidgetClass_4_1.Succeeded() || !S_WidgetClass_4_2.Succeeded() || !C_WidgetClass_4_2.Succeeded() ||
		!S_WidgetClass_5_1.Succeeded() || !C_WidgetClass_5_1.Succeeded() || !S_WidgetClass_5_2.Succeeded() || !C_WidgetClass_5_2.Succeeded() ||
		!S_WidgetClass_3_3.Succeeded() || !C_WidgetClass_3_3.Succeeded() || !S_WidgetClass_4_3.Succeeded() || !C_WidgetClass_4_3.Succeeded()
		)
	{
		GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("FClassFinder Failed"));
	}

	ServerWidgetClass.AddUnique(S_WidgetClass_1_1.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_2_1.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_2_2.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_2_3.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_3_1.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_3_2.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_3_3.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_4_1.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_4_2.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_4_3.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_5_1.Class);
	ServerWidgetClass.AddUnique(S_WidgetClass_5_2.Class);

	ClientWidgetClass.AddUnique(C_WidgetClass_1_1.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_2_1.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_2_2.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_2_3.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_3_1.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_3_2.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_3_3.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_4_1.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_4_2.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_4_3.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_5_1.Class);
	ClientWidgetClass.AddUnique(C_WidgetClass_5_2.Class);

	ServerWidgets.Init(NULL, ServerWidgetClass.Num());// ServerWidgetClass의 개수만큼 메모리 공간 확보

	MediaPath = FString("./Movies/Low/2.mp4");

	score = 0;

	static ConstructorHelpers::FObjectFinder<USoundWave> Transition06(TEXT("SoundWave'/Game/Sound/Widget/트랜지션_06.트랜지션_06'"));

	Transition_06 = Transition06.Object;
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	DeltaRotation = false;

	MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());

	if (HasAuthority())
	{
		UWidgetLayoutLibrary::RemoveAllWidgets(this);

		ServerWidgets[ServerWidgetIndex::ServerWidget_1_1] = CreateWidget<UServerWidget_1_1>(GetWorld(), ServerWidgetClass[ServerWidgetIndex::ServerWidget_1_1]);

		if (IsValid(ServerWidgets[ServerWidgetIndex::ServerWidget_1_1]))
		{
			ServerWidgets[ServerWidgetIndex::ServerWidget_1_1]->AddToViewport();
		}
	}
	else
	{
		auto ClientWidget_1_1 = CreateWidget<UClientWidget_1_1>(this, ClientWidgetClass[ClientWidgetIndex::ClientWidget_1_1]);

		if (IsValid(ClientWidget_1_1))
		{
			ClientWidget_1_1->AddToViewport();
		}
	}

	delegate.BindUFunction(this, FName("FindSeek"));

}

void AMainPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AMainPlayerController, score);
}

void AMainPlayerController::FindSeek()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("FindSeek"));
	UServerWidget_5_2* temp = Cast<UServerWidget_5_2>(ServerWidgets[ServerWidgetIndex::ServerWidget_5_2]);

	temp->MediaPlayer->Play();
}

void AMainPlayerController::SetMediaPath_Implementation(uint8 selectlevel, uint8 selcet_button)
{
	auto ServerPC=Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ServerPC->Level = selectlevel;
	ServerPC->SelectButton = selcet_button;
	Referee::Referee_Level = (SelectLevel)selectlevel;
	Referee::Referee_Button = (Select_Button)selcet_button;

	switch (selectlevel)
	{
		case Low:
			ServerPC->MediaPath = MainGameInstance->Low_MediaPath[selcet_button - 1];
			ServerPC->MediaPath_Side = MainGameInstance->Low_MediaPath_Side[selcet_button - 1];
			break;
		case Middle:
			ServerPC->MediaPath = MainGameInstance->Middle_MediaPath[selcet_button - 1];
			ServerPC->MediaPath_Side = MainGameInstance->Middle_MediaPath_Side[selcet_button - 1];
			break;
		case High:
			ServerPC->MediaPath = MainGameInstance->High_MediaPath[selcet_button - 1];
			ServerPC->MediaPath_Side = MainGameInstance->High_MediaPath_Side[selcet_button - 1];
			break;
		default:
			break;
	}
}


void AMainPlayerController::SetUserData_Hight_Implementation(int hight, int32 index)
{
		MainGameInstance->User_Hight = hight;
		auto Widget = Cast<UServerWidget_2_2>(ServerWidgets[ServerWidgetIndex::ServerWidget_2_2]);
		Widget->ListView_Hight->SetSelectedIndex(index);
}

void AMainPlayerController::SetUserData_Sex_Implementation(const FString& sex, int32 index)
{
		MainGameInstance->User_Sex = sex;
		auto Widget = Cast<UServerWidget_2_2>(ServerWidgets[ServerWidgetIndex::ServerWidget_2_2]);
		Widget->ListView_Sex->SetSelectedIndex(index);
}

void AMainPlayerController::NextHelperImage_Implementation()
{
	auto HelperWidget = Cast<UServerWidget_2_1>(ServerWidgets[ServerWidgetIndex::ServerWidget_2_1]);

	if (HelperWidget->loading)
	{
		if (++HelperWidget->CurPathIndex >= HelperWidget->MaxPathIndex)
		{
			HelperWidget->CurPathIndex = HelperWidget->MaxPathIndex - 1;
		}
		HelperWidget->SetZOrder(HelperWidget->CurPathIndex);
		//HelperWidget->SetMediaPath_Video(HelperWidget->VideoPathes[HelperWidget->CurPathIndex]);
		HelperWidget->SetTextGuide(HelperWidget->CurPathIndex);
	}
}

void AMainPlayerController::PreHelperImage_Implementation()
{
	auto HelperWidget = Cast<UServerWidget_2_1>(ServerWidgets[ServerWidgetIndex::ServerWidget_2_1]);

	if (HelperWidget->loading)
	{
		if (--HelperWidget->CurPathIndex < 0)
		{
			HelperWidget->CurPathIndex = 0;
		}
		HelperWidget->SetZOrder(HelperWidget->CurPathIndex);
		//HelperWidget->SetMediaPath_Video(HelperWidget->VideoPathes[HelperWidget->CurPathIndex]);
		HelperWidget->SetTextGuide(HelperWidget->CurPathIndex);
	}
}

void AMainPlayerController::ShowServerWidget_Implementation(uint8 index, uint8 level = 0, uint8 button_index = 0)
{
	//UGameplayStatics::PlaySound2D(this, Transition_06);

	UWidgetLayoutLibrary::RemoveAllWidgets(this);// !!가비지 컬렉터가 객체를 지우고 ServerWidget[index]는 쓰레기를 가리키는 포인터로 남는다?

	switch (index)
	{
		case ServerWidgetIndex::ServerWidget_1_1:
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_1_1>(GetWorld(), ServerWidgetClass[index]);
			}
			break;
		case ServerWidgetIndex::ServerWidget_2_1 :
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_2_1>(GetWorld(), ServerWidgetClass[index]);
			}
			break;
		case ServerWidgetIndex::ServerWidget_2_2 :
			//해당 위젯의 NativeConstruct()의 AddItem 함수가 중복 호출되는 것을 방지하기 위해 매번 새로 위젯을 생성한다.
			ServerWidgets[index] = CreateWidget<UServerWidget_2_2>(GetWorld(), ServerWidgetClass[index]);
			break;
		case ServerWidgetIndex::ServerWidget_2_3 :
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_2_3>(GetWorld(), ServerWidgetClass[index]);
			}
			break;
		case ServerWidgetIndex::ServerWidget_3_1 :
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_3_1>(GetWorld(), ServerWidgetClass[index]);
			}
			break;
		case ServerWidgetIndex::ServerWidget_3_2:
			Level = level;
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_3_2>(GetWorld(), ServerWidgetClass[index]);
			}
			// !!이미 만들어진 위젯의 변수가 바뀌었을때, 왜 NativeConstruct()가 호출되는지 모름. 아마 객체가 매번 새로 만들어 지는 듯.
			// 위젯이 뷰포트에 추가될 때 NativeConstruct() 호출.
			break;	
		case ServerWidgetIndex::ServerWidget_3_3:
			UServerWidget_3_3::Level = (SelectLevel)level;
			UServerWidget_3_3::Button = (Select_Button)button_index;
			UPictogram::Level = (SelectLevel)level;
			UPictogram::Button = (Select_Button)button_index;
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_3_3>(GetWorld(), ServerWidgetClass[index]);
			}
			break;
		case ServerWidgetIndex::ServerWidget_4_1:
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_4_1>(GetWorld(), ServerWidgetClass[index]);
			}
			break;
		case ServerWidgetIndex::ServerWidget_4_2:
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_4_2>(GetWorld(), ServerWidgetClass[index]);
			}
			break;
		case ServerWidgetIndex::ServerWidget_4_3:
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_4_3>(GetWorld(), ServerWidgetClass[index]);
			}
			break;
		case ServerWidgetIndex::ServerWidget_5_1:
			/*if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_5_1>(GetWorld(), ServerWidgetClass[index]);
			}*/
			ServerWidgets[index] = CreateWidget<UServerWidget_5_1>(GetWorld(), ServerWidgetClass[index]);
			break;
		case ServerWidgetIndex::ServerWidget_5_2:
			if (ServerWidgets[index] == NULL)
			{
				ServerWidgets[index] = CreateWidget<UServerWidget_5_2>(GetWorld(), ServerWidgetClass[index]);
			}
			break;
		case ServerWidgetIndex::NextCoachingVideo:
			UPictogram::Level = (SelectLevel)level;
			UPictogram::Button = (Select_Button)button_index;
			if (ServerWidgets[ServerWidget_4_3] == NULL)
			{
				ServerWidgets[ServerWidget_4_3] = CreateWidget<UServerWidget_4_3>(GetWorld(), ServerWidgetClass[ServerWidget_4_3]);
			}
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Wrong Server index"));

	}

	if (index == ServerWidgetIndex::NextCoachingVideo)
	{
		ServerWidgets[ServerWidget_4_3]->AddToViewport();
	}
	else if (IsValid(ServerWidgets[index]))
	{
		ServerWidgets[index]->AddToViewport();
	}

}

void AMainPlayerController::Sync_ListView_Implementation(float a)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("%f"), a));
	auto ServerWidget = Cast<UServerWidget_2_2>(ServerWidgets[ServerWidgetIndex::ServerWidget_2_2]);
	ServerWidget->ListView_Hight->SetScrollOffset(a);
}


void AMainPlayerController::ShowClientWidget_Implementation(uint8 ClientWidgetIndex)
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	UUserWidget* ClientWidget;
	switch (ClientWidgetIndex)
	{
		case ClientWidgetIndex::ClientWidget_1_1:

			ClientWidget = CreateWidget<UClientWidget_1_1>(this, ClientWidgetClass[ClientWidgetIndex::ClientWidget_1_1]);

			if (IsValid(ClientWidget))
			{
				ClientWidget->AddToViewport();
			}
			break;

		case ClientWidgetIndex::ClientWidget_3_1:

			ClientWidget = CreateWidget<UClientWidget_3_1>(this, ClientWidgetClass[ClientWidgetIndex::ClientWidget_3_1]);

			if (IsValid(ClientWidget))
			{
				ClientWidget->AddToViewport();
			}
			break;

		case ClientWidgetIndex::ClientWidget_4_2:
			ClientWidget = CreateWidget<UClientWidget_4_2>(this, ClientWidgetClass[ClientWidgetIndex::ClientWidget_4_2]);

			if (IsValid(ClientWidget))
			{
				ClientWidget->AddToViewport();
			}
			break;

		case ClientWidgetIndex::ClientWidget_4_3:
			ClientWidget = CreateWidget<UClientWidget_4_3>(this, ClientWidgetClass[ClientWidgetIndex::ClientWidget_4_3]);

			if (IsValid(ClientWidget))
			{
				ClientWidget->AddToViewport();
			}
			break;

		case ClientWidgetIndex::ClientWidget_5_1:
			ClientWidget = CreateWidget<UClientWidget_5_1>(this, ClientWidgetClass[ClientWidgetIndex::ClientWidget_5_1]);

			if (IsValid(ClientWidget))
			{
				ClientWidget->AddToViewport();
			}
			break;
		default:
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, TEXT("Wrong Client index"));

	}
	
}

void AMainPlayerController::NextCoachingVideo_Implementation()
{
	auto ServerPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	switch (ServerPC->Level)
	{
	case Low:
		if (++ServerPC->SelectButton <= MainGameInstance->Low_MediaPath.Num())
		{
			ServerPC->MediaPath = MainGameInstance->Low_MediaPath[ServerPC->SelectButton - 1];
			ServerPC->MediaPath_Side = MainGameInstance->Low_MediaPath_Side[ServerPC->SelectButton - 1];
			ServerPC->ShowServerWidget(ServerWidgetIndex::NextCoachingVideo, Low, ServerPC->SelectButton);
		}
		else
		{
			ServerPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_1);
			ShowClientWidget(ClientWidgetIndex::ClientWidget_3_1);
		}
		break;
	case Middle:
		if (++ServerPC->SelectButton <= MainGameInstance->Middle_MediaPath.Num())
		{
			ServerPC->MediaPath = MainGameInstance->Middle_MediaPath[ServerPC->SelectButton - 1];
			ServerPC->MediaPath_Side = MainGameInstance->Middle_MediaPath_Side[ServerPC->SelectButton - 1];
			ServerPC->ShowServerWidget(ServerWidgetIndex::NextCoachingVideo, Middle, ServerPC->SelectButton);
		}
		else
		{
			ServerPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_1);
			ShowClientWidget(ClientWidgetIndex::ClientWidget_3_1);
		}
		break;
	case High:
		if (++ServerPC->SelectButton <= MainGameInstance->High_MediaPath.Num())
		{
			ServerPC->MediaPath = MainGameInstance->High_MediaPath[ServerPC->SelectButton - 1];
			ServerPC->MediaPath_Side = MainGameInstance->High_MediaPath_Side[ServerPC->SelectButton - 1];
			ServerPC->ShowServerWidget(ServerWidgetIndex::NextCoachingVideo, High, ServerPC->SelectButton);
		}
		else
		{
			ServerPC->ShowServerWidget(ServerWidgetIndex::ServerWidget_3_1);
			ShowClientWidget(ClientWidgetIndex::ClientWidget_3_1);
		}
		break;
	default:
		break;
	}
}

void AMainPlayerController::SetMediaPlayerRate_Implementation(int32 rate)
{
	UServerWidget_5_2* temp = Cast<UServerWidget_5_2>(ServerWidgets[ServerWidgetIndex::ServerWidget_5_2]);

	//temp->MediaPlayer->OnSeekCompleted.AddDynamic(this, &AMainPlayerController::FindSeek);
	temp->MediaPlayer->OnSeekCompleted.AddUnique(delegate);
	
	if (rate == 3)//기존의 빨리감기 버튼을 클릭하면 들어오는 값
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("fast"));
		temp->MediaPlayer->Pause();
		int32 time = temp->MediaPlayer->GetTime().GetTotalSeconds() + 3.0;
		FTimespan Timespan = FTimespan::FromSeconds(time);
		if (Timespan > temp->MediaPlayer->GetDuration())
			Timespan = temp->MediaPlayer->GetDuration();

		temp->MediaPlayer->Seek(Timespan);
		//temp->MediaPlayer->Play();
	}
	else if (rate == 2)//기존의 느리게감기 버튼을 클릭하면 들어오는 값
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("slow"));
		temp->MediaPlayer->Pause();
		int32 time = temp->MediaPlayer->GetTime().GetTotalSeconds() - 3.0;
		FTimespan Timespan = FTimespan::FromSeconds(time);
		if (Timespan < FTimespan::Zero())
			Timespan = FTimespan::Zero();

		temp->MediaPlayer->Seek(Timespan);
		//temp->MediaPlayer->Play();
	}
	else//1.0or0.0
	{
		temp->MediaPlayer->SetRate(rate);
	}


	//기획 수정 : 재생속도 변경 -> 일정 프레임 이후로 재생.
	/*temp->MediaPlayer->SetRate(rate);
	temp->TextBlock_Rate->SetText(FText::FromString(FString::Printf(TEXT("%.1fx"), rate)));*/
}


void AMainPlayerController::SyncMediaDuration_Implementation(double CurPerDu)
{
	ClientWidget_5_2->Seeker->SetValue(CurPerDu);
}

void AMainPlayerController::SeekMediaPlayer_Implementation(double SeekValue)
{
	UServerWidget_5_2* temp = Cast<UServerWidget_5_2>(ServerWidgets[ServerWidgetIndex::ServerWidget_5_2]);
	double time = SeekValue * (temp->Duration);

	FTimespan timespan = FTimespan::FromSeconds(time);

	if (!(temp->MediaPlayer->Seek(timespan)))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Purple, TEXT("Fail to Seek."));
	}
}

void AMainPlayerController::ClickButton_2_2_Pressed_Implementation(const FString& button_name)
{
	auto temp = Cast<UServerWidget_2_2>(ServerWidgets[ServerWidgetIndex::ServerWidget_2_2]);

	temp->Image_Sex_Toggle->SetVisibility(ESlateVisibility::Collapsed);
	temp->Image_Hight_Toggle->SetVisibility(ESlateVisibility::Collapsed);

	if (button_name == FString(TEXT("Sex")))
	{
		temp->S_bar->SetVisibility(ESlateVisibility::Visible);
		temp->Image_Sex_Toggle->SetVisibility(ESlateVisibility::Visible);
		temp->Image_Sex_Back->SetVisibility(ESlateVisibility::Visible);
		temp->ListView_Sex->SetVisibility(ESlateVisibility::Visible);
	}
	else if(button_name == FString(TEXT("Hight")))
	{
		temp->Image_Hight_Toggle->SetVisibility(ESlateVisibility::Visible);
		temp->Image_Hight_Back->SetVisibility(ESlateVisibility::Visible);
		temp->ListView_Hight->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainPlayerController::ClickButton_2_2_Released_Implementation()
{
	auto temp = Cast<UServerWidget_2_2>(ServerWidgets[ServerWidgetIndex::ServerWidget_2_2]);

	temp->Image_Sex_Toggle->SetVisibility(ESlateVisibility::Collapsed);
	temp->Image_Hight_Toggle->SetVisibility(ESlateVisibility::Collapsed);
}


void AMainPlayerController::ClickButton_2_3_Pressed_Implementation(const FString& button_name)
{
	auto temp = Cast<UServerWidget_2_3>(ServerWidgets[ServerWidgetIndex::ServerWidget_2_3]);

	temp->Image_Userdata_Toggle->SetVisibility(ESlateVisibility::Collapsed);
	temp->Image_Enter_Toggle->SetVisibility(ESlateVisibility::Collapsed);


	if (button_name == FString(TEXT("Userdata")))
	{
		temp->Image_Userdata_Toggle->SetVisibility(ESlateVisibility::Visible);
	}
	else if (button_name == FString(TEXT("Enter")))
	{
		temp->Image_Enter_Toggle->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainPlayerController::ClickButton_2_3_Released_Implementation()
{
	auto temp = Cast<UServerWidget_2_3>(ServerWidgets[ServerWidgetIndex::ServerWidget_2_3]);

	temp->Image_Userdata_Toggle->SetVisibility(ESlateVisibility::Collapsed);
	temp->Image_Enter_Toggle->SetVisibility(ESlateVisibility::Collapsed);
}

void AMainPlayerController::ClickButton_3_1_Pressed_Implementation(const FString& button_name)
{
	auto temp = Cast<UServerWidget_3_1>(ServerWidgets[ServerWidgetIndex::ServerWidget_3_1]);

	temp->LowLevel_Toggle->SetVisibility(ESlateVisibility::Collapsed);
	temp->MiddleLevel_Toggle->SetVisibility(ESlateVisibility::Collapsed);
	temp->HighLevel_Toggle->SetVisibility(ESlateVisibility::Collapsed);


	if (button_name == FString(TEXT("LowLevel")))
	{
		temp->LowLevel_Toggle->SetVisibility(ESlateVisibility::Visible);
	}
	else if (button_name == FString(TEXT("MiddleLevel")))
	{
		temp->MiddleLevel_Toggle->SetVisibility(ESlateVisibility::Visible);
	}
	else if (button_name == FString(TEXT("HighLevel")))
	{
		temp->HighLevel_Toggle->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMainPlayerController::ClickButton_3_1_Released_Implementation()
{
	auto temp = Cast<UServerWidget_3_1>(ServerWidgets[ServerWidgetIndex::ServerWidget_3_1]);

	temp->LowLevel_Toggle->SetVisibility(ESlateVisibility::Collapsed);
	temp->MiddleLevel_Toggle->SetVisibility(ESlateVisibility::Collapsed);
	temp->HighLevel_Toggle->SetVisibility(ESlateVisibility::Collapsed);
}
