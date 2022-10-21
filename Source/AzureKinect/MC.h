// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Anim_MC.h"
#include "Components/InputComponent.h"
#include "MC.generated.h"

UCLASS()
class AZUREKINECT_API AMC : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMC();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
		void AttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	

	UPROPERTY(VisibleAnywhere, Category = Skeletal)
		USkeletalMeshComponent* Body;
	UPROPERTY(BlueprintReadOnly)
		UAnim_MC* Anim_MC;

	FString FilePath;
	int32 FrameNum;
	bool MotagePlaying;
};
