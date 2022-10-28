// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AzureKinect.h"
#include "Widget/IncludeWidgets.h"
#include "MainGameInstance.h"
#include "GameFramework/PlayerController.h"
#include "CustomEnum.h"
#include "Net/UnrealNetwork.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMainPlayerController();

	virtual void BeginPlay();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

private:
	static Referee* referee;

public:

	UFUNCTION()
		void FindSeek();
	FScriptDelegate delegate;

	inline Referee* GetReferee() { return referee; };

	UPROPERTY()
		UMainGameInstance* MainGameInstance;
	UPROPERTY()
		TArray<TSubclassOf<UUserWidget>> ServerWidgetClass;
	UPROPERTY()
		TArray<TSubclassOf<UUserWidget>> ClientWidgetClass;

	UPROPERTY()
		TArray<UUserWidget*> ServerWidgets;

	UPROPERTY()
		UClientWidget_5_2* ClientWidget_5_2;

	UPROPERTY(BlueprintReadOnly)
		FString MediaPath;
	UPROPERTY(BlueprintReadOnly)
		FString MediaPath_Side;
	uint8 Level;
	uint8 SelectButton;

	UPROPERTY(replicated)
		int32 score;

	UPROPERTY()
		USoundWave* Transition_06;

	UPROPERTY(BlueprintReadOnly)
		bool DeltaRotation;

	//RPC함수는 [함수명]_Implementation() 으로 구현
	UFUNCTION(Server, Reliable)
		void ShowServerWidget(uint8 index, uint8 level = 0, uint8 button_index = 0);
	UFUNCTION(Server, Reliable)
		void NextHelperImage();
	UFUNCTION(Server, Reliable)
		void PreHelperImage();
	UFUNCTION(Server, Reliable)
		void SetUserData_Hight(int hight, int32 index);
	UFUNCTION(Server, Reliable)
		void SetUserData_Sex(const FString& sex, int32 index);
	UFUNCTION(Server, Reliable)
		void ClickButton_2_2_Pressed(const FString& button_name);
	UFUNCTION(Server, Reliable)
		void ClickButton_2_2_Released();
	UFUNCTION(Server, Reliable)
		void ClickButton_2_3_Pressed(const FString& button_name);
	UFUNCTION(Server, Reliable)
		void ClickButton_2_3_Released();
	UFUNCTION(Server, Reliable)
		void ClickButton_3_1_Pressed(const FString& button_name);
	UFUNCTION(Server, Reliable)
		void ClickButton_3_1_Released();
	UFUNCTION(Server, Reliable)
		void SetMediaPath(uint8 selectlevel, uint8 selcet_button);
	UFUNCTION(Server, Reliable)
		void Sync_ListView(float a);
	UFUNCTION(Client, Reliable)
		void ShowClientWidget(uint8 ClientWidgetIndex);
	UFUNCTION(Server, Reliable)
		void NextCoachingVideo();
	UFUNCTION(Server, Reliable)
		void SetMediaPlayerRate(int32 rate);
	UFUNCTION(Client, Reliable)
		void SyncMediaDuration(double CurPerDu);
	UFUNCTION(Server, Reliable)
		void SeekMediaPlayer(double SeekValue);
};
