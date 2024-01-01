

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

<<<<<<< HEAD
void AAIPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	 
}

AActor* AAIPlayerController::GetClosestEnemy() const
{
	const ABaseCharacter* OwnerCharacter=Cast<ABaseCharacter>(GetCharacter());
=======
AActor* AAIPlayerController::GetClosestEnemy() const
{
	ABaseCharacter* OwnerCharacter=Cast<ABaseCharacter>(GetCharacter());
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
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
<<<<<<< HEAD
 
void AAIPlayerController::LookForwardEnemy()
{  
	const UBlackboardComponent* BlackBoard=GetBlackboardComponent(); 
	if(!BlackBoard)return;
	AActor* ClosestEnemy=Cast<AActor>(BlackBoard->GetValueAsObject(BlackBoardEnemyKey)); 
	SetFocus(ClosestEnemy); 
=======

void AAIPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	LookForwardClosestEnemy();
}

void AAIPlayerController::LookForwardClosestEnemy()
{
	const UBlackboardComponent* BlackBoard=GetBlackboardComponent(); 
	if(!BlackBoard)return;
	AActor* ClosestEnemy=Cast<AActor>(BlackBoard->GetValueAsObject(BlackBoardEnemyKey)); 
	SetFocus(ClosestEnemy);
	
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
}
