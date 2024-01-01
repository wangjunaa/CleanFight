
#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "AICharacter.generated.h"
 
UCLASS()
class CLEANFIGHT_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
<<<<<<< HEAD
public: 

	UFUNCTION(BlueprintCallable)
=======
public:
	AAICharacter(); 

>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
	void Fire();
	void Aiming();
	void EndAiming();
	virtual void OnDeath(AController* InstigatedBy) override;
<<<<<<< HEAD
	virtual void BeginPlay() override;
=======
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
};
