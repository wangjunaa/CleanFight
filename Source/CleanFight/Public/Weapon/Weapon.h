
#pragma once

#include "CoreMinimal.h" 
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


class AWeaponModule;
class AProjectile; 
UCLASS()
class CLEANFIGHT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	UFUNCTION(BlueprintCallable,Category="Weapon")
	FVector GetMuzzleLocation() const;
	
	UFUNCTION(BlueprintCallable,Category="Weapon")
	float GetFireRate() const {return FireRate+FireRateOffset;}

	UFUNCTION(BlueprintCallable,Category="Weapon")
	void MakeShoot(const FVector& TargetPoint) const;
	
	UFUNCTION(BlueprintCallable,Category="Weapon")
	int GetMaxModuleNumber() const;

	UFUNCTION(BlueprintCallable,Category="Weapon")
	void SetMaxModuleNumber(int Value);
	UFUNCTION(BlueprintCallable,Category="UI")
	UMaterial* GetIcon() const;

	UFUNCTION(BlueprintCallable,Category="Weapon")
	TArray<AWeaponModule*> GetWeaponModules() const;
	
	UFUNCTION(BlueprintCallable,Category="Weapon")
	bool AddModule(AWeaponModule* Module,int Index=-1); 
	UFUNCTION(BlueprintCallable,Category="Weapon")
	void ClearModule();
	UFUNCTION(BlueprintCallable,Category="Weapon")
	bool RemoveModule(int Index);
	
	UFUNCTION(BlueprintCallable,Category="Weapon")
	USkeletalMeshComponent* GetMesh() const{return WeaponMesh;};
	UFUNCTION(BlueprintCallable,Category="Module")
	void AddProjectileDamage(float Amount){ProjectileDamageOffset+=Amount;};
	UFUNCTION(BlueprintCallable,Category="Module")
	void AddProjectileSpeed(float Amount){ProjectileSpeedOffset+=Amount;};
	UFUNCTION(BlueprintCallable,Category="Module")
	void AddFireRate(float Amount){FireRate+=Amount;};
	UFUNCTION(BlueprintCallable,Category="Module")
	void AddProjectileScale(float Amount){ProjectileScaleOffset+=Amount;};
	
	UFUNCTION(BlueprintCallable,Category="Module")
	void SetVisibility(bool Flag) const {WeaponMesh->SetVisibility(Flag);};

	UPROPERTY(EditAnywhere,Category="Weapon")
	FString WeaponName;
 
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
	float FireRateOffset=0;
	UPROPERTY(EditAnywhere,Category="Weapon")
	int MaxModuleNumber=5;
	UPROPERTY(EditAnywhere,Category="Weapon")
	TArray<AWeaponModule*>WeaponModules;
	float ProjectileScaleOffset=1;
	float ProjectileSpeedOffset=0;
	float ProjectileDamageOffset=0;
	
	UPROPERTY(EditAnywhere,Category="Weapon")
	TSubclassOf<AProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly,Category	="UI")
	TObjectPtr<UMaterial> WeaponIcon;
};
