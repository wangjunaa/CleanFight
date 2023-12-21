
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLEANFIGHT_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Weapon")
	FName WeaponSocketName="WeaponSocket";

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Blueprintable,Category="Weapon")
	AWeapon* GetCurrentWeapon() const {return CurrentWeapon;}
	UFUNCTION(Blueprintable,Category="Weapon")
	TSubclassOf<AWeapon> GetCurrentWeaponClass();
	
	void OnStartFire();
	void MakeShoot() const;
	void OnEndFire();

	UFUNCTION(Blueprintable)
	bool IsFiring(){return Firing;}
	
private:
	
	UFUNCTION(Blueprintable,Category="Weapon")
	FTransform GetWeaponSocketTransform() const;
	
	void GetAimLine(FVector& TargetPoint) const;

	AController* GetOwnerController() const;

	int CurrentWeaponIndex=0;
	UPROPERTY(EditAnywhere,Category="Weapon")
	TArray<TSubclassOf<AWeapon>> WeaponList;

	FTimerHandle FireTimerHandle;
	
	TObjectPtr<AWeapon> CurrentWeapon=nullptr;

	void SpawnWeapon();
	bool Firing=false;
};
