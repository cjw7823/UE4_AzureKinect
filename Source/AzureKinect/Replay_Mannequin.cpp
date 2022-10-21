// Fill out your copyright notice in the Description page of Project Settings.

#include "Replay_Mannequin.h"
#include "AzureKinectHelper.h"
#include "RePlayAnimInstance.h"
#include "MainGameInstance.h"

// Sets default values
AReplay_Mannequin::AReplay_Mannequin()
{
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKELETAL"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CAMERA"));
	Body->SetupAttachment(RootComponent);
	SpringArm->SetupAttachment(Body);
	Camera->SetupAttachment(SpringArm);
	SpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, -90.0f));
	Camera->FOVAngle = 60.0f;
	SpringArm->TargetArmLength = 200.0f;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Male(TEXT("SkeletalMesh'/Game/Character/User_Doll/SK_HS_maleDoll_retextured.SK_HS_maleDoll_retextured'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Female(TEXT("SkeletalMesh'/Game/Character/User_Doll/SK_HS_femaleDoll_retextured.SK_HS_femaleDoll_retextured'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Kid(TEXT("SkeletalMesh'/Game/Character/User_Doll/SK_HS_kidDoll_retextured.SK_HS_kidDoll_retextured'"));
	SK_Male = Male.Object;
	SK_Female = Female.Object;
	SK_Kid = Kid.Object;

	if (Male.Succeeded())
	{
		Body->SetSkeletalMesh(Male.Object);
	}
	Body->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> BP_AnimMannequin(TEXT("AnimBlueprint'/Game/Blueprints/BP_AnimReplay.BP_AnimReplay_C'"));
	if (BP_AnimMannequin.Succeeded())
	{
		Body->SetAnimInstanceClass(BP_AnimMannequin.Class);
	}

	ReplayTransform.Init(FTransform(FRotator(0.f,0.f,0.f), FVector(NULL)), (int32)EKinectBodyJointId::COUNT);


	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Left_Arm(TEXT("Material'/Game/Character/User_Material/Left_Arm.Left_Arm'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Left_Leg(TEXT("Material'/Game/Character/User_Material/Left_Leg.Left_Leg'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Right_Arm(TEXT("Material'/Game/Character/User_Material/Right_Arm.Right_Arm'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Right_Leg(TEXT("Material'/Game/Character/User_Material/Right_Leg.Right_Leg'"));
	Leftarm = Left_Arm.Object;
	Leftleg = Left_Leg.Object;
	Rightarm = Right_Arm.Object;
	Rightleg = Right_Leg.Object;

}

// Called when the game starts or when spawned
void AReplay_Mannequin::BeginPlay()
{
	Super::BeginPlay();

	Dyn_Leftarm = UMaterialInstanceDynamic::Create(Leftarm, this);
	Dyn_Leftleg = UMaterialInstanceDynamic::Create(Leftleg, this);
	Dyn_Rightarm = UMaterialInstanceDynamic::Create(Rightarm, this);
	Dyn_Rightleg = UMaterialInstanceDynamic::Create(Rightleg, this);

	Dyn_Leftarm->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 1.f));
	Dyn_Leftleg->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 1.f));
	Dyn_Rightarm->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 1.f));
	Dyn_Rightleg->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 1.f));

	Body->SetMaterial(1, Dyn_Leftarm);
	Body->SetMaterial(2, Dyn_Leftleg);
	Body->SetMaterial(3, Dyn_Rightarm);
	Body->SetMaterial(4, Dyn_Rightleg);
}

// Called every frame
void AReplay_Mannequin::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Cast<URePlayAnimInstance>(Body->GetAnimInstance())->JointsTransform_C = ReplayTransform;
}

void AReplay_Mannequin::SetReplayTransform(uint8 index, float pitch, float yaw, float roll)
{
	FTransform temp = FTransform(FRotator(pitch, yaw, roll), FVector(NULL), FVector(NULL));
	ReplayTransform[index] = temp;
}

void AReplay_Mannequin::SetSkeletalMesh()
{
	auto temp = Cast<UMainGameInstance>(GetGameInstance());
	if (temp->User_Hight <= 140)
	{
		Body->SetSkeletalMesh(SK_Kid);
		Body->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.8f));
	}
	else if (temp->User_Sex == TEXT("남자"))
	{
		Body->SetSkeletalMesh(SK_Male);
		Body->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
	else
	{
		Body->SetSkeletalMesh(SK_Female);
		Body->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	}
}

void AReplay_Mannequin::SetMeshColor(float leftarm, float rightarm, float leftleg, float rightleg)
{
	//100 == 파랑, 50 == 노랑, 25 == 빨강
	if (leftarm == -1)
	{
		Dyn_Leftarm->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 1.f));
		Dyn_Rightarm->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 1.f));
		Dyn_Leftleg->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 1.f));
		Dyn_Rightleg->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 1.f));
	}
	else
	{
		if (leftarm >= 75)
		{
			Dyn_Leftarm->SetVectorParameterValue("Param", FLinearColor(0.f, 0.f, 1.f));
		}
		else if (leftarm >= 30)
		{
			Dyn_Leftarm->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 0.f));
		}
		else
		{
			Dyn_Leftarm->SetVectorParameterValue("Param", FLinearColor(1.f, 0.f, 0.f));
		}

		if (rightarm >= 75)
		{
			Dyn_Rightarm->SetVectorParameterValue("Param", FLinearColor(0.f, 0.f, 1.f));
		}
		else if (rightarm >= 30)
		{
			Dyn_Rightarm->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 0.f));
		}
		else
		{
			Dyn_Rightarm->SetVectorParameterValue("Param", FLinearColor(1.f, 0.f, 0.f));
		}

		if (leftleg >= 75)
		{
			Dyn_Leftleg->SetVectorParameterValue("Param", FLinearColor(0.f, 0.f, 1.f));
		}
		else if (leftleg >= 30)
		{
			Dyn_Leftleg->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 0.f));
		}
		else
		{
			Dyn_Leftleg->SetVectorParameterValue("Param", FLinearColor(1.f, 0.f, 0.f));
		}

		if (rightleg >= 75)
		{
			Dyn_Rightleg->SetVectorParameterValue("Param", FLinearColor(0.f, 0.f, 1.f));
		}
		else if (rightleg >= 30)
		{
			Dyn_Rightleg->SetVectorParameterValue("Param", FLinearColor(1.f, 1.f, 0.f));
		}
		else
		{
			Dyn_Rightleg->SetVectorParameterValue("Param", FLinearColor(1.f, 0.f, 0.f));
		}
	}
}

