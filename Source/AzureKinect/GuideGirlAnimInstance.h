// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GuideGirlAnimInstance.generated.h"

UENUM(BlueprintType)
enum class WidgetIndex : uint8
{
	ServerWidget_1_1 = 0,
	ServerWidget_2_1, //Helper widget
	ServerWidget_2_2,
	ServerWidget_2_3,
	ServerWidget_3_1,
	ServerWidget_3_2,
	ServerWidget_3_3,
	ServerWidget_4_1,
	ServerWidget_4_2,
	ServerWidget_4_3,
	ServerWidget_5_1,
	ServerWidget_5_2,
	None,
};

UENUM(BlueprintType)
enum class ButtonIndex : uint8
{
	None = 0,
	Button_1 = 1,
	Button_2 = 2,
	Button_3 = 3,
	Button_4 = 4,
	Button_5 = 5,
};

UENUM(BlueprintType)
enum class CoachingLevel : uint8
{
	Low = 0,
	Middle,
	High,
	Level_None,
};

/**
 * 
 */
UCLASS()
class AZUREKINECT_API UGuideGirlAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
		WidgetIndex WidgetIndex;

	UPROPERTY(BlueprintReadOnly)
		ButtonIndex ButtonIndex;

	UPROPERTY(BlueprintReadOnly)
		CoachingLevel CoachingLevel;

	UPROPERTY(BlueprintReadOnly)
		bool Count;

	UPROPERTY(BlueprintReadWrite)
		UAudioComponent* AudioCom;
		
};
