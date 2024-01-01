
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Fire.generated.h"
 
UCLASS()
class CLEANFIGHT_API UBTTask_Fire : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Fire();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetEnemy;
	UPROPERTY(EditAnywhere)
	float FireRange=300;
};
