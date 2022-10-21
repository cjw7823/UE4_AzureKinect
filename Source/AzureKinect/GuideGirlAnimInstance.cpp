// Fill out your copyright notice in the Description page of Project Settings.

#include "GuideGirlAnimInstance.h"
#include "Kismet/GameplayStatics.h"


void UGuideGirlAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	WidgetIndex = WidgetIndex::None;
	ButtonIndex = ButtonIndex::None;
	CoachingLevel = CoachingLevel::Level_None;
	Count = false;
}