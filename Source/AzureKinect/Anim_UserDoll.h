// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Anim_UserDoll.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API UAnim_UserDoll : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
		TArray<FTransform> JointsTransform_C;
};
