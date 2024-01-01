
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookForwardEnemy.generated.h"
 
UCLASS()
class CLEANFIGHT_API UBTTask_LookForwardEnemy : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTask_LookForwardEnemy();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	 
};
