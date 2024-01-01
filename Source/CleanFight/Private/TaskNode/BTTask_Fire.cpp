

#include "TaskNode/BTTask_Fire.h"

#include "AIController.h" 
<<<<<<< HEAD
#include "BehaviorTree/BlackboardComponent.h"
=======
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
#include "Character/AICharacter.h"

UBTTask_Fire::UBTTask_Fire()
{
	NodeName="Fire";
}

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
<<<<<<< HEAD
	AAICharacter* Character=Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	const auto BlackBoard= OwnerComp.GetBlackboardComponent();
	const auto Enemy=Cast<ABaseCharacter>(BlackBoard->GetValueAsObject(TargetEnemy.SelectedKeyName));
	const float Distance=(Enemy->GetActorLocation()-Character->GetActorLocation()).Length();
	if(!Character || !Enemy || Distance>FireRange)
		return EBTNodeResult::Failed;
	Character->Fire();
	
=======
	 AAICharacter* Character=Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetCharacter());
	if(!Character)return EBTNodeResult::Failed;
	Character->Fire();
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
	return EBTNodeResult::Succeeded;
}
