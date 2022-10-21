// Fill out your copyright notice in the Description page of Project Settings.

#include "Widget/EntryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/ClientWidget_2_1.h"
#include "SocketSubsystem.h"
#include "MainGameInstance.h"
#include "MainPlayerController.h"
#include <string>

#define SESSION_NAME FName("1")

void UEntryWidget::NativeConstruct()
{
	//Super::NativeConstruct();
	Server_Button->OnClicked.AddDynamic(this, &UEntryWidget::OnClick_ServerButton);
	Client_Button->OnClicked.AddDynamic(this, &UEntryWidget::OnClick_ClientButton);
	UClientWidget_2_1::isFirst = true;

	FText IP = FText::FromString(GetMyIpAddress());
	TextBlock_MyIP->SetText(IP);
}

void UEntryWidget::OnClick_ServerButton()
{
	auto MainGI = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (subGI == nullptr)
	{
		subGI = MainGI->GetSubsystem<UMainGameInstanceSubsystem>();
		subGI->CreateSession(2, true);
		//subGI->UpdateSession();
		subGI->StartSession();
	}

	if(subGI != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("Click!"));
}

void UEntryWidget::OnClick_ClientButton()
{

	auto MainGI = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (subGI == nullptr)
	{
		subGI = MainGI->GetSubsystem<UMainGameInstanceSubsystem>();
		subGI->FindSessions(1, true);
		circle->SetVisibility(ESlateVisibility::Visible);
	}


	if (subGI != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("Click!"));
}

FString UEntryWidget::GetMyIpAddress()
{
	FString IPAddr = FString("");

	bool canBind = false;

	TSharedRef<FInternetAddr> LocalIP = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, canBind);

	if (LocalIP->IsValid())
	{
		IPAddr = LocalIP->ToString(false);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Blue, LocalIP->ToString(false));
	return IPAddr;
}
