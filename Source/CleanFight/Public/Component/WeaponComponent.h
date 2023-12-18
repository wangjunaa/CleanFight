
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

	UPROPERTY(EditAnywhere,Category="Weapon")
	TObjectPtr<AWeapon> CurrentWeapon;
	
	void OnStartFire();
	void OnEndFire();
private:
	
	UFUNCTION(Blueprintable,Category="Weapon")
	FTransform GetWeaponSocketTransform() const;
	
	void GetAimLine(FVector& StartPoint,FVector& EndPoint);

	AController* GetOwnerController();
};
