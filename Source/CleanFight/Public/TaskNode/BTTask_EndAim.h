
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_EndAim.generated.h"
 
UCLASS()
class CLEANFIGHT_API UBTTask_EndAim : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_EndAim();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
