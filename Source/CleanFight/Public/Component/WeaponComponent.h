
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


class AWeaponModule;
class UNiagaraSystem;
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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	

	UFUNCTION(BlueprintCallable,Category="Weapon")
	AWeapon* GetCurrentWeapon() const; 
	UFUNCTION(BlueprintCallable,Category="Weapon")
	TArray<AWeapon*> GetWeaponList()const; 
	UFUNCTION(BlueprintCallable,Category="Weapon")
	UMaterial* GetCurrentWeaponIcon() const; 
	UFUNCTION(BlueprintCallable,Category="Weapon")
	int GetCurrentWeaponIndex() const; 
	void Fire();
	void MakeShoot(); 
	UFUNCTION(BlueprintCallable,Category="Weapon")
	bool AddWeapon(AWeapon* NewWeapon);
	UFUNCTION(BlueprintCallable,Server,Reliable,Category="Weapon")
	void RemoveWeapon(int Index);
	
	UFUNCTION(BlueprintCallable,Server,Reliable,Category="Weapon")
	void NextWeapon();
	UFUNCTION(BlueprintCallable,Server,Reliable,Category="Weapon")
	void LastWeapon();
	
	UFUNCTION(BlueprintCallable,Category="Bag")
	TArray<AWeaponModule*> GetModuleBag() const;
	UFUNCTION(BlueprintCallable,Category="Bag")
	bool AddToBag(AWeaponModule* WeaponModule,int Index=-1); 
	UFUNCTION(BlueprintCallable,Category="Weapon")
	void ClearBag();
	UFUNCTION(BlueprintCallable,Category="Bag")
	bool RemoveFromBag(int Index);
	UFUNCTION(BlueprintCallable,Category="Bag")
	int GetMaxBagNum() const;
private:
	
	FTransform GetWeaponSocketTransform() const;
	FVector GetFireTargetPoint() const;
	FVector GetAimPoint() const;

	AController* GetOwnerController() const;

	int CurrentWeaponIndex=0;
	UPROPERTY(EditAnywhere,Category="Weapon")
	TArray<TSubclassOf<AWeapon>> DefaultWeaponClassList;
	UPROPERTY(EditAnywhere,Category="VFX")
	TObjectPtr<UNiagaraSystem>SwitchWeaponVfx;
	UPROPERTY(Replicated)
	TArray<AWeapon*> WeaponList;
	  
	FTimerHandle FireCDTimerHandle;
	UFUNCTION(Server,Reliable)
	void SpawnWeapon(); 
	bool bFireInCD=false;
	void FireCDFinish(){bFireInCD=false;}
	float FireRange=10000;
	int MaxWeaponNumber=4;
	
	UPROPERTY(Replicated)
	TArray<AWeaponModule*> ModuleBag;
	int MaxBagNum=132;
};
