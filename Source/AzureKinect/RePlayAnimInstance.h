// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RePlayAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API URePlayAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
		TArray<FTransform> JointsTransform_C;
	UPROPERTY(BlueprintReadWrite)
		float TransformAlpha_C;
};
