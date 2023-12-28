
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStateComponent.generated.h"


class AWeaponModule;
class UCapsuleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLEANFIGHT_API UPlayerStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerStateComponent();
	UFUNCTION(BlueprintCallable,Category="State")
	void AddState(UTexture2D* Texture,int Num=1) ;

	UFUNCTION(BlueprintCallable,Category="State")
	TMap<UTexture2D*,int> GetState() ;
	
	UFUNCTION(BlueprintCallable,Category="Bag")
	TArray<AWeaponModule*> GetBag() const;
	UFUNCTION(BlueprintCallable,Category="Bag")
	bool AddToBag(AWeaponModule* WeaponModule,int Index=-1);
	UFUNCTION(BlueprintCallable,Category="Bag")
	bool RemoveFromBag(AWeaponModule* WeaponModule,int Index);
protected:
	virtual void BeginPlay() override;
	
private:  
	TMap<UTexture2D*,int> PlayerState;
	TArray<AWeaponModule*> Bag;
	int MaxBagNum=56;
};
