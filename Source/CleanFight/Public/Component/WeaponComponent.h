
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

	UFUNCTION(BlueprintCallable,Category="Weapon")
	AWeapon* GetCurrentWeapon() const { return CurrentWeapon;	}
	UFUNCTION(BlueprintCallable,Category="Weapon")
	TSubclassOf<AWeapon> GetCurrentWeaponClass(); 
	
	void Fire();
	void MakeShoot(); 
  
private:
	// UPROPERTY(EditAnywhere,Category="Montage")
	// TObjectPtr<UAnimMontage>FireMontage;
	
	FTransform GetWeaponSocketTransform() const;
	FVector GetFireTargetPoint() const;
	FVector GetAimPoint() const;

	AController* GetOwnerController() const;

	int CurrentWeaponIndex=0;
	UPROPERTY(EditAnywhere,Category="Weapon")
	TArray<TSubclassOf<AWeapon>> WeaponList;

	FTimerHandle FireCDTimerHandle;
	
	TObjectPtr<AWeapon> CurrentWeapon=nullptr;

	void SpawnWeapon(); 
	bool bFireInCD=false;
	void FireCDFinish(){bFireInCD=false;}
	float FireRange=10000;
};
