

#include "BTService/BTService_FindClossestEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AIPlayerController.h"

void UBTService_FindClossestEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if(UBlackboardComponent* Blackboard=OwnerComp.GetBlackboardComponent())
	{ 
		if(const AAIPlayerController* AIController= Cast<AAIPlayerController>(OwnerComp.GetAIOwner()) )
		{ 
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName,AIController->GetClosestEnemy());
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
