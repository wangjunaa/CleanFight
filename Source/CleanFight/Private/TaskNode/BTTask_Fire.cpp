

#include "TaskNode/BTTask_Fire.h"

#include "AIController.h" 
#include "Character/AICharacter.h"

UBTTask_Fire::UBTTask_Fire()
{
	NodeName="Fire";
}

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	 AAICharacter* Character=Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if(!Character)return EBTNodeResult::Failed;
	Character->Fire();
	return EBTNodeResult::Succeeded;
}
