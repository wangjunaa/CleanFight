

#include "BTService/BTService_LookForwardEnemy.h"
 
#include "Character/AIPlayerController.h"

void UBTService_LookForwardEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIPlayerController* Owner= Cast<AAIPlayerController>(OwnerComp.GetAIOwner()); 
	   
	Owner->LookForwardEnemy(); 
}
