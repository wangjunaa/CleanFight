

#include "Character/AICharacter.h"

#include "Components/WidgetComponent.h"

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
 