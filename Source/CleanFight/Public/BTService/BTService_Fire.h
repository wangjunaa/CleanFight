
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Fire.generated.h"
UCLASS()
class CLEANFIGHT_API UBTService_Fire : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_Fire();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
