// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "CustomEnum.h"
#include "ClientWidget_2_1.generated.h"


class AMainPlayerController;
class UClientWidget_2_2;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UClientWidget_2_1 : public UUserWidget
{
	GENERATED_BODY()
		virtual void NativeConstruct() override;
		virtual void NativeDestruct() override;
		virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
		void SetMediaPath_Background();

public:
	UClientWidget_2_1(const FObjectInitializer& ObjectInitializer);
	//최초 실행 판단을 위한 변수, 'EntryWidget'에서 true, this->OnClick_Button_Next()에서 false로 변경. 기본값=true
	static bool isFirst;
	static SelectLevel Level;
	static Select_Button Button;

	/*
	다른 위젯에서 this를 생성할 때, 호출한 위젯의 정보를 저장 시켜줘야 한다.
	OnClick_Button_Close()호출 시 다시 생성할 위젯을 결정해야 하기 때문.
	*/
	static ServerWidgetIndex Index;

	uint8 Image_Procedure_Index;
	TArray<UImage*> Image_Procedures;

	bool loading;
	UFUNCTION()
		void FirstZOrder();
	UFUNCTION()
		void OnClick_Button_left();
	UFUNCTION()
		void OnClick_Button_right();
	UFUNCTION()
		void OnClick_Button_Next();
	UFUNCTION()
		void OnClick_Button_Close();

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Background;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;

	UPROPERTY(meta = (bindwidget))
		UButton* Button_left;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_right;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Next;
	UPROPERTY(meta = (bindwidget))
		UButton* Button_Close;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Procedure_1;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Procedure_2;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Procedure_3;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Procedure_4;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Procedure_5;

	UPROPERTY()
		AMainPlayerController* MainPC;
	UPROPERTY()
		UClientWidget_2_2* ClientWidget_2_2;

	UPROPERTY()
		USoundWave* Button_14;
	UPROPERTY()
		USoundWave* Button_09;

	int32 InitTimer;
	UFUNCTION()
		void CheckInitTimer();
	FTimerHandle InitTimerhandle;
};