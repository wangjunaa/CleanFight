

#include "Character/AICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Character/AIPlayerController.h"
<<<<<<< HEAD
 
=======

AAICharacter::AAICharacter()
{
	
}

>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
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
<<<<<<< HEAD
	
=======
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
}

void AAICharacter::OnDeath(AController* InstigatedBy)
{
	if(const AAIPlayerController* AIPlayerController=Cast<AAIPlayerController>(GetController()))
	{
		AIPlayerController->BrainComponent->Cleanup();
	}
	Super::OnDeath(InstigatedBy);
}
<<<<<<< HEAD

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
}
=======
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
 
  