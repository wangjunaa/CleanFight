
#pragma once

#include "CoreMinimal.h" 
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class AProjectile; 
UCLASS()
class CLEANFIGHT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	UFUNCTION(Blueprintable,Category="Weapon")
	FVector GetMuzzleLocation() const;
	
	UFUNCTION(Blueprintable,Category="Weapon")
	float GetFireRate() const {return FireRate;}

	UFUNCTION(Blueprintable,Category="Weapon")
	void MakeShoot(const FVector& TargetPoint) const;
	
	UPROPERTY(EditAnywhere,Category="Weapon")
	TSubclassOf<AProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly,Category	="UI")
	TObjectPtr<UMaterial> WeaponIcon;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Scene;
	UPROPERTY(VisibleAnywhere,Category="Weapon") 
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	
	UPROPERTY(VisibleAnywhere,Category="Weapon")
	FName MuzzleSocketName="MuzzleSocket";

private: 
	UPROPERTY(VisibleAnywhere,Category="Weapon")
	float FireRate=0.3;

};
