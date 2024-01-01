// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskNode/BTTask_EndAim.h"

#include "AIController.h"
#include "Character/AICharacter.h"

UBTTask_EndAim::UBTTask_EndAim()
{
	NodeName="EndAim";
}

EBTNodeResult::Type UBTTask_EndAim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{ 
	AAICharacter* Character=Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if(!Character)return EBTNodeResult::Failed;
	Character->EndAiming();
	return EBTNodeResult::Succeeded;
}
