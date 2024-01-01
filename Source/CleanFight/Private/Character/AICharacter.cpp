

#include "Character/AICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Character/AIPlayerController.h"
 
void AAICharacter::Fire() 
{
	Action_OnFire();
}

void AAICharacter::Aiming()
{
	bAiming=true;
}

void AAICharacter::EndAiming()
{
	bAiming=false;
	
}

void AAICharacter::OnDeath(AController* InstigatedBy)
{
	if(const AAIPlayerController* AIPlayerController=Cast<AAIPlayerController>(GetController()))
	{
		AIPlayerController->BrainComponent->Cleanup();
	}
	Super::OnDeath(InstigatedBy);
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}
 
  