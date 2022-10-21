// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_MC.h"
#define path "AnimMontage'/Game/Animation/T_Pose_UE4_Mannequin_Montage.T_Pose_UE4_Mannequin_Montage'"

UAnim_MC::UAnim_MC()
{
    static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT(path));
    if (ATTACK_MONTAGE.Succeeded())
    {
        AttackMontage = ATTACK_MONTAGE.Object;
    }
}

void UAnim_MC::PlayAttackMontage()
{
    if (!Montage_IsPlaying(AttackMontage))
    {
        Montage_Play(AttackMontage, 1.0f);
    }
}
