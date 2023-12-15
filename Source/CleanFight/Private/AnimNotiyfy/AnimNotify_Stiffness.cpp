// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotiyfy/AnimNotify_Stiffness.h"

#include "AnimationUtils.h"
#include "Character/BaseCharacter.h"

void UAnimNotify_Stiffness::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{ 
	if(ABaseCharacter* Character=Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		UE_LOG(LogAnimNotify,Display,TEXT("僵直"));
		Character->StartStiffness();
	}
}
