

#include "TaskNode/BTTask_LookForwardEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AIPlayerController.h"

UBTTask_LookForwardEnemy::UBTTask_LookForwardEnemy()
{
	NodeName="LookForward";
}

EBTNodeResult::Type UBTTask_LookForwardEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPlayerController* Owner= Cast<AAIPlayerController>(OwnerComp.GetAIOwner());  
	if(!Owner)return EBTNodeResult::Failed;
	 
	Owner->LookForwardEnemy();
	return EBTNodeResult::Succeeded;
}

