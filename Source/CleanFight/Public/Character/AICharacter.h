
#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "AICharacter.generated.h"
 
UCLASS()
class CLEANFIGHT_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AAICharacter(); 

	void Fire();
	void Aiming();
	void EndAiming();
	virtual void OnDeath() override;
};
