
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UNiagaraSystem;
class UHitVFXComponent;
class UProjectileMovementComponent;
class USphereComponent;
UCLASS()
class CLEANFIGHT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnProjectileHit(
		UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit
		);
public:	
	UPROPERTY(VisibleAnywhere,Category="Projectile")
	TObjectPtr<USphereComponent> CollisionComp;
	
	UPROPERTY(VisibleAnywhere,Category="Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere,Category="Projectile")
	TObjectPtr<UNiagaraSystem> BodyVfx;
	  
	UPROPERTY(VisibleAnywhere,Category="Projectile")
	TObjectPtr<UHitVFXComponent> HitVfxComp;
	 
	
	UPROPERTY(EditAnywhere,Category="Damage")
	int ProjectileDamage=10;
	
	UPROPERTY(EditAnywhere,Category="Damage")
	TSubclassOf<UDamageType> DamageType=nullptr;
	UPROPERTY(EditAnywhere,Category="Damage|Explore")
	bool bExplore=false;

	UPROPERTY(EditAnywhere,Category="Damage|Explore",meta=(EditCondition="bExplore"))
	int ExploreRadius=100;
	
	UPROPERTY(EditAnywhere,Category="Damage|Explore",meta=(EditCondition="bExplore"))
	bool bDoFullDamage=true;
	UPROPERTY(EditAnywhere,Category="Damage|Explore",meta=(EditCondition="bExplore"))
	TObjectPtr<UNiagaraSystem> ExploreVfx=nullptr;
private:
	void Explore();
	FTimerHandle FireTimerHandle;
 
};
