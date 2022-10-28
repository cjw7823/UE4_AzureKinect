// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "FileMediaSource.h"
#include "/work/ue4_azure_kinect/Source/AzureKinect/Anim_UserDoll.h"
#include "ServerWidget_4_3.generated.h"

class AMainPlayerController;
/**
 * 
 */
UCLASS()
class AZUREKINECT_API UServerWidget_4_3 : public UUserWidget
{
	GENERATED_BODY()

public:
	UServerWidget_4_3(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override; //Json data 저장 준비.
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void SetCoachingVideo();
	void SetCoachingVideo_Side();
	void SetUserVideo();

	UFUNCTION()
		void CountDown();
	/*UFUNCTION()
		FText Textbinding();*/

	UFUNCTION()
		void CheckOpenResource(FString OpenedUrl);
	UFUNCTION()
		void FailOpenResource(FString OpenedUrl);
	UFUNCTION()
		void EndPlay();//Json data 저장 완료. 파일 저장.
	UFUNCTION()
		void PlaybackSuspended();
	UFUNCTION()
		void PlaybackResumed();
	UFUNCTION()
		void Save_to_Jsonfile();

	bool is_OpenResource;
	bool is_Play;
	FTimerHandle timerhandle;
	bool once;

	UPROPERTY(BlueprintReadWrite)
	int32 Count;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Coaching;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_User;
	UPROPERTY(meta = (bindwidget))
		UImage* Image_Indexmap;
	UPROPERTY()
		UMediaTexture* MediaTexture;
	UPROPERTY()
		UMediaPlayer* MediaPlayer;
	UPROPERTY()
		UFileMediaSource* FileMediaSource;
	UPROPERTY()
		UMaterial* User_Material;
	UPROPERTY(meta = (bindwidget))
		UTextBlock* TextBlock_Count;

	UPROPERTY(meta = (bindwidget))
		UImage* Image_Coaching_Side;
	UPROPERTY()
		UMediaTexture* MediaTexture_Side;
	UPROPERTY()
		UMediaPlayer* MediaPlayer_Side;
	UPROPERTY()
		UFileMediaSource* FileMediaSource_Side;

	UPROPERTY()
		AMainPlayerController* MainPC;

	UPROPERTY()
		USoundWave* Button_04;

	UPROPERTY(meta = (bindwidget))
		UUserWidget* Pictogram_0;

public:
	FString FilePath;
	int64 FrameNum;
	TSubclassOf<AActor> Doll;
	UAnim_UserDoll* Anim_UserDoll;
};
