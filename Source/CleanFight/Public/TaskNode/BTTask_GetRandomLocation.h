
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetRandomLocation.generated.h"
 
UCLASS()
class CLEANFIGHT_API UBTTask_GetRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTask_GetRandomLocation();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//寻路半径
	UPROPERTY(EditAnywhere)
	float Radius=1000;
	//设值键
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector LocationKey;
	//是否以自我为中心寻路
	UPROPERTY(EditAnywhere)
	bool SelfCenter=true;
	UPROPERTY(EditAnywhere,meta=(EditCondition="!SelfCenter"))
	FBlackboardKeySelector CenterActorKey;
};
