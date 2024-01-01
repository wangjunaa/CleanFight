

#include "TaskNode/BTTask_Fire.h"

#include "AIController.h" 
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter.h"

UBTTask_Fire::UBTTask_Fire()
{
	NodeName="Fire";
}

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	AAICharacter* Character=Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	const auto BlackBoard= OwnerComp.GetBlackboardComponent();
	const auto Enemy=Cast<ABaseCharacter>(BlackBoard->GetValueAsObject(TargetEnemy.SelectedKeyName));
	const float Distance=(Enemy->GetActorLocation()-Character->GetActorLocation()).Length();
	if(!Character || !Enemy || Distance>FireRange)
		return EBTNodeResult::Failed;
	Character->Fire();
	
	return EBTNodeResult::Succeeded;
}
