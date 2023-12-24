

#include "BTService/BTService_Fire.h"
 
#include "AIController.h"
#include "Character/AICharacter.h"


UBTService_Fire::UBTService_Fire()
{
	NodeName="Fire";
}

void UBTService_Fire::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if(AAICharacter* AICharacter=Cast<AAICharacter>(OwnerComp.GetAIOwner()->GetCharacter()))
	{
		AICharacter->Aiming();
		AICharacter->Fire();
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
