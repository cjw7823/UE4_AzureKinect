// Fill out your copyright notice in the Description page of Project Settings.


#include "MC.h"
#include "Kismet/GameplayStatics.h"

#define FILENAME "PleaseDelete.txt"

FString Json_String_;
TSharedRef<TJsonWriter<TCHAR>> Writer1 = TJsonWriterFactory<>::Create(&Json_String_);
AMC::AMC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETAL"));
	Body->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Male(TEXT("SkeletalMesh'/Game/Character/User_Doll/SK_HS_maleDoll_ueJoint.SK_HS_maleDoll_ueJoint'"));
	if (Male.Succeeded())
	{
		Body->SetSkeletalMesh(Male.Object);
	}
	Body->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_AnimMannequin(TEXT("AnimBlueprint'/Game/Motion_Capture/Anim_MC.Anim_MC_C'"));
	if (BP_AnimMannequin.Succeeded())
	{
		Body->SetAnimInstanceClass(BP_AnimMannequin.Class);
	}

	FilePath = FPaths::ProjectDir() + TEXT("UserData/MC_Data/") + TEXT(FILENAME);
	Json_String_ = NULL;
	MotagePlaying = false;
}

// Called when the game starts or when spawned
void AMC::BeginPlay()
{
	Super::BeginPlay();
	Writer1 = TJsonWriterFactory<>::Create(&Json_String_);
	Writer1->WriteObjectStart();

	MotagePlaying = false;
	Anim_MC = Cast<UAnim_MC>(Body->GetAnimInstance());
	Anim_MC->PlayAttackMontage();
	MotagePlaying = true;
	
	FrameNum = 0;
	Json_String_ = NULL;
	Anim_MC->OnMontageEnded.AddDynamic(this, &AMC::AttackMontageEnded);
	
}

void AMC::Tick(float DeltaSeconds)
{
	auto upperarm_l = Body->GetBoneIndex(FName("upperarm_l"));
	auto temp1 = Body->GetBoneTransform(upperarm_l).GetRotation().Rotator().ToString();
	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Blue, "upperarm_l : " + temp1);
	auto lowerarm_l = Body->GetBoneIndex(FName("lowerarm_l"));
	auto temp2 = Body->GetBoneTransform(lowerarm_l).GetRotation().Rotator().ToString();
	GEngine->AddOnScreenDebugMessage(2, 10, FColor::Blue, "lowerarm_l : " + temp2);
	auto upperarm_r = Body->GetBoneIndex(FName("upperarm_r"));
	auto temp3 = Body->GetBoneTransform(upperarm_r).GetRotation().Rotator().ToString();
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Blue, "upperarm_r : " + temp3);
	auto lowerarm_r = Body->GetBoneIndex(FName("lowerarm_r"));
	auto temp4 = Body->GetBoneTransform(lowerarm_r).GetRotation().Rotator().ToString();
	GEngine->AddOnScreenDebugMessage(4, 10, FColor::Blue, "lowerarm_r : " + temp4);
	auto thigh_l = Body->GetBoneIndex(FName("thigh_l"));
	auto temp5 = Body->GetBoneTransform(thigh_l).GetRotation().Rotator().ToString();
	GEngine->AddOnScreenDebugMessage(5, 10, FColor::Blue, "thigh_l : " + temp5);
	auto calf_l = Body->GetBoneIndex(FName("calf_l"));
	auto temp6 = Body->GetBoneTransform(calf_l).GetRotation().Rotator().ToString();
	GEngine->AddOnScreenDebugMessage(6, 10, FColor::Blue, "calf_l : " + temp6);
	auto thigh_r = Body->GetBoneIndex(FName("thigh_r"));
	auto temp7 = Body->GetBoneTransform(thigh_r).GetRotation().Rotator().ToString();
	GEngine->AddOnScreenDebugMessage(7, 10, FColor::Blue, "thigh_r : " + temp7);
	auto calf_r = Body->GetBoneIndex(FName("calf_r"));
	auto temp8 = Body->GetBoneTransform(calf_r).GetRotation().Rotator().ToString();
	GEngine->AddOnScreenDebugMessage(8, 10, FColor::Blue, "calf_r : " +temp8);


	if (MotagePlaying)
	{
		FrameNum += 1;
		Writer1->WriteObjectStart(FString::FromInt(FrameNum));

		auto index = Body->GetBoneIndex(FName("upperarm_l"));
		if(index == INDEX_NONE)
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Fail to find bone."));
		FRotator rotation = Body->GetBoneTransform(index).GetRotation().Rotator();
		//GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Orange, FString::Printf(TEXT("%f"), rotation.Pitch));
		Writer1->WriteObjectStart(FString(TEXT("SHOULDER_LEFT")));
		Writer1->WriteValue(FString(TEXT("Pitch")), rotation.Pitch);
		Writer1->WriteValue(FString(TEXT("Yaw")), rotation.Yaw);
		Writer1->WriteValue(FString(TEXT("Roll")), rotation.Roll);
		Writer1->WriteObjectEnd();

		index = Body->GetBoneIndex(FName("lowerarm_l"));
		if (index == INDEX_NONE)
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Fail to find bone."));
		rotation = Body->GetBoneTransform(index).GetRotation().Rotator();

		Writer1->WriteObjectStart(FString(TEXT("ELBOW_LEFT")));
		Writer1->WriteValue(FString(TEXT("Pitch")), rotation.Pitch);
		Writer1->WriteValue(FString(TEXT("Yaw")), rotation.Yaw);
		Writer1->WriteValue(FString(TEXT("Roll")), rotation.Roll);
		Writer1->WriteObjectEnd();

		index = Body->GetBoneIndex(FName("upperarm_r"));
		if (index == -1)
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Fail to find bone."));
		rotation = Body->GetBoneTransform(index).GetRotation().Rotator();

		Writer1->WriteObjectStart(FString(TEXT("SHOULDER_RIGHT")));
		Writer1->WriteValue(FString(TEXT("Pitch")), rotation.Pitch);
		Writer1->WriteValue(FString(TEXT("Yaw")), rotation.Yaw);
		Writer1->WriteValue(FString(TEXT("Roll")), rotation.Roll);
		Writer1->WriteObjectEnd();

		index = Body->GetBoneIndex(FName("lowerarm_r"));
		if (index == -1)
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Fail to find bone."));
		rotation = Body->GetBoneTransform(index).GetRotation().Rotator();

		Writer1->WriteObjectStart(FString(TEXT("ELBOW_RIGHT")));
		Writer1->WriteValue(FString(TEXT("Pitch")), rotation.Pitch);
		Writer1->WriteValue(FString(TEXT("Yaw")), rotation.Yaw);
		Writer1->WriteValue(FString(TEXT("Roll")), rotation.Roll);
		Writer1->WriteObjectEnd();

		index = Body->GetBoneIndex(FName("thigh_l"));
		if (index == -1)
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Fail to find bone."));
		rotation = Body->GetBoneTransform(index).GetRotation().Rotator();

		Writer1->WriteObjectStart(FString(TEXT("HIP_LEFT")));
		Writer1->WriteValue(FString(TEXT("Pitch")), rotation.Pitch);
		Writer1->WriteValue(FString(TEXT("Yaw")), rotation.Yaw);
		Writer1->WriteValue(FString(TEXT("Roll")), rotation.Roll);
		Writer1->WriteObjectEnd();

		index = Body->GetBoneIndex(FName("calf_l"));
		if (index == -1)
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Fail to find bone."));
		rotation = Body->GetBoneTransform(index).GetRotation().Rotator();

		Writer1->WriteObjectStart(FString(TEXT("KNEE_LEFT")));
		Writer1->WriteValue(FString(TEXT("Pitch")), rotation.Pitch);
		Writer1->WriteValue(FString(TEXT("Yaw")), rotation.Yaw);
		Writer1->WriteValue(FString(TEXT("Roll")), rotation.Roll);
		Writer1->WriteObjectEnd();

		index = Body->GetBoneIndex(FName("thigh_r"));
		if (index == -1)
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Fail to find bone."));
		rotation = Body->GetBoneTransform(index).GetRotation().Rotator();

		Writer1->WriteObjectStart(FString(TEXT("HIP_RIGHT")));
		Writer1->WriteValue(FString(TEXT("Pitch")), rotation.Pitch);
		Writer1->WriteValue(FString(TEXT("Yaw")), rotation.Yaw);
		Writer1->WriteValue(FString(TEXT("Roll")), rotation.Roll);
		Writer1->WriteObjectEnd();

		index = Body->GetBoneIndex(FName("calf_r"));
		if (index == -1)
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Fail to find bone."));
		rotation = Body->GetBoneTransform(index).GetRotation().Rotator();

		Writer1->WriteObjectStart(FString(TEXT("KNEE_RIGHT")));
		Writer1->WriteValue(FString(TEXT("Pitch")), rotation.Pitch);
		Writer1->WriteValue(FString(TEXT("Yaw")), rotation.Yaw);
		Writer1->WriteValue(FString(TEXT("Roll")), rotation.Roll);
		Writer1->WriteObjectEnd();


		Writer1->WriteObjectEnd();
	}
}

void AMC::AttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	MotagePlaying = false;

	Writer1->WriteValue(FString(TEXT("TOTAL_FRAME")), FrameNum);
	Writer1->WriteObjectEnd();
	Writer1->Close();

	FFileHelper::SaveStringToFile(*Json_String_, *FilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), true);

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Orange, TEXT("Finish save_file"));

	auto MainPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//MainPC->ConsoleCommand("quit");
}

#undef FILENAME