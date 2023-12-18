
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class CLEANFIGHT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	UFUNCTION(Blueprintable,Category="Weapon")
	FVector GetMuzzleLocation() const;
protected:
	virtual void BeginPlay();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Scene;
	UPROPERTY(VisibleAnywhere,Category="Weapon") 
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere,Category="Weapon")
	FName MuzzleSocketName="MuzzleSocket";
private:	
};
