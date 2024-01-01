
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
<<<<<<< HEAD
	virtual void Tick(float DeltaSeconds) override;
=======
	
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComp;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY(EditAnywhere)
	FName BlackBoardEnemyKey="EnemyActor";

	AActor* GetClosestEnemy() const;
<<<<<<< HEAD
	void LookForwardEnemy();


private: 
=======
private:
	virtual void Tick(float DeltaSeconds) override;
	void LookForwardClosestEnemy();   
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
	
};
