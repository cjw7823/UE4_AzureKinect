// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Anim_MC.generated.h"

/**
 * 
 */
UCLASS()
class AZUREKINECT_API UAnim_MC : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_MC();

	void PlayAttackMontage();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;
};
