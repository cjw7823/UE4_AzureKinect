// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AzureKinect.h"
#include "GameFramework/Character.h"
#include "Materials/MaterialInstance.h"
#include "Replay_Mannequin.generated.h"

UCLASS()
class AZUREKINECT_API AReplay_Mannequin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AReplay_Mannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void SetReplayTransform(uint8 index, float pitch, float yaw, float roll);
	void SetSkeletalMesh();
	void SetMeshColor(int32 leftarm, int32 rightarm, int32 leftleg, int32 rightleg);

	UPROPERTY(VisibleAnywhere, Category = Skeletal)
		USkeletalMeshComponent* Body;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		USceneCaptureComponent2D* Camera;
	UPROPERTY(BlueprintReadOnly)
		TArray<FTransform> ReplayTransform;
	UPROPERTY()
		USkeletalMesh* SK_Male;
	UPROPERTY()
		USkeletalMesh* SK_Female;
	UPROPERTY()
		USkeletalMesh* SK_Kid;

	UPROPERTY()
		UMaterialInstanceDynamic* Dyn_Leftarm;
	UPROPERTY()
		UMaterialInstanceDynamic* Dyn_Rightarm;
	UPROPERTY()
		UMaterialInstanceDynamic* Dyn_Leftleg;
	UPROPERTY()
		UMaterialInstanceDynamic* Dyn_Rightleg;

	UPROPERTY()
		UMaterialInterface* Leftarm;
	UPROPERTY()
		UMaterialInterface* Leftleg;
	UPROPERTY()
		UMaterialInterface* Rightarm;
	UPROPERTY()
		UMaterialInterface* Rightleg;
};
