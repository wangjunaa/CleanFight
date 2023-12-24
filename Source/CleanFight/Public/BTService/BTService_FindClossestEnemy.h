
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FindClossestEnemy.generated.h"
 
UCLASS()
class CLEANFIGHT_API UBTService_FindClossestEnemy : public UBTService
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
