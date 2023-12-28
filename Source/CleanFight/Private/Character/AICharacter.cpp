

#include "Character/AICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Character/AIPlayerController.h"

AAICharacter::AAICharacter()
{
	
}

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
 
  