

#include "TaskNode\BTTask_GetRandomLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation()
{
	NodeName="GetRandomLocation";
}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* Owner= OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard=OwnerComp.GetBlackboardComponent();
	if(!Owner||!Blackboard)return EBTNodeResult::Failed;

	APawn* Pawn=Owner->GetPawn();
	if(!Pawn)return EBTNodeResult::Failed;

	//获取当前导航信息
	const UNavigationSystemV1* NaviSystem= UNavigationSystemV1::GetCurrent(Pawn);
	if(!NaviSystem)return EBTNodeResult::Failed;
	FNavLocation NavLocation;
	const AActor* CenterActor=Pawn;
	if(!SelfCenter)
	{
		CenterActor=Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
	}
	const bool IsFound = NaviSystem->GetRandomReachablePointInRadius(CenterActor->GetActorLocation(), Radius, NavLocation); 
		  
	Blackboard->SetValueAsVector(LocationKey.SelectedKeyName,NavLocation);
	return EBTNodeResult::Succeeded;
}
