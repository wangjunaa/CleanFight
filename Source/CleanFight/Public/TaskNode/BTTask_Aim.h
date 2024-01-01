
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Aim.generated.h"
 
UCLASS()
class CLEANFIGHT_API UBTTask_Aim : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Aim();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
