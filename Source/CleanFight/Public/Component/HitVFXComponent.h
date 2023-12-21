
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitVFXComponent.generated.h"


class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLEANFIGHT_API UHitVFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHitVFXComponent();

protected:
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere,Category="VFX")
	UNiagaraSystem* DefaultEffect=nullptr;

	UPROPERTY(EditAnywhere,Category="VFX")
	TMap<UPhysicalMaterial*,UNiagaraSystem*>Effects;

	UPROPERTY(EditAnywhere,Category="VFX")
	bool PlayVFXByHitRotation=true;
	void PlayVfxOnHit(const FHitResult& HitResult);
		
};
