

#include "TaskNode/BTTask_Aim.h"

#include "AIController.h"
#include "Character/AICharacter.h"

UBTTask_Aim::UBTTask_Aim()
{
	NodeName="Aim";
}

EBTNodeResult::Type UBTTask_Aim::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAICharacter* Character=Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if(!Character)return EBTNodeResult::Failed;
	Character->Aiming();
	return EBTNodeResult::Succeeded;
}
