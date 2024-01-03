
#pragma once

#include "CoreMinimal.h"
#include "AIController.h" 
#include "Perception/AIPerceptionComponent.h"
#include "AIPlayerController.generated.h"
 
UCLASS()
class CLEANFIGHT_API AAIPlayerController : public AAIController
{
	GENERATED_BODY()
public:
	AAIPlayerController(); 
	virtual void OnPossess(APawn* InPawn) override;  
	virtual void Tick(float DeltaSeconds) override;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY(EditAnywhere)
	FName BlackBoardEnemyKey="EnemyActor";

	AActor* GetClosestEnemy() const;
	void LookForwardEnemy();

	
private: 
	
};
