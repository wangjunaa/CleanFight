

#include "Character/AIPlayerController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/BaseCharacter.h"
#include "Perception/AISense_Sight.h"
DEFINE_LOG_CATEGORY_STATIC(LogAiPlayerController,All,All)
AAIPlayerController::AAIPlayerController()
{
	PrimaryActorTick.bCanEverTick=true;
	AIPerceptionComp=CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComp");
}
 

void AAIPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTree);

}

void AAIPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	 
}

AActor* AAIPlayerController::GetClosestEnemy() const
{
	const ABaseCharacter* OwnerCharacter=Cast<ABaseCharacter>(GetCharacter());
	if(!OwnerCharacter)return nullptr;
	TArray<AActor*> Actors;
	//获取视野中所有actor
	AIPerceptionComp->GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),Actors);

	float MinimumDis=MAX_int32;
	ABaseCharacter* ClosestCharacter=nullptr;
	for (const auto Actor : Actors)
	{
		//判断角色是否死亡或队友
		ABaseCharacter* BaseCharacter=Cast<ABaseCharacter>(Actor);
		if(BaseCharacter && !BaseCharacter->IsTeamMate(OwnerCharacter->GetTeamName()) && !BaseCharacter->IsDeath())
		{
			const float Dis=(OwnerCharacter->GetActorLocation()-BaseCharacter->GetActorLocation()).Size();
			if(Dis<MinimumDis)
			{
				MinimumDis=Dis;
				ClosestCharacter=BaseCharacter;
			}
		}
	}
	return ClosestCharacter;
}
 
void AAIPlayerController::LookForwardEnemy()
{  
	const UBlackboardComponent* BlackBoard=GetBlackboardComponent(); 
	if(!BlackBoard)return;
	AActor* ClosestEnemy=Cast<AActor>(BlackBoard->GetValueAsObject(BlackBoardEnemyKey)); 
	SetFocus(ClosestEnemy); 
}
