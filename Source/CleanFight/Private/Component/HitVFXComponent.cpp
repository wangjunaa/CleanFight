

#include "Component/HitVFXComponent.h"

#include "NiagaraFunctionLibrary.h"

UHitVFXComponent::UHitVFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}


void UHitVFXComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHitVFXComponent::PlayVfxOnHit(const FHitResult& HitResult)
{
	if(!DefaultEffect)return;
	UNiagaraSystem* Effect=DefaultEffect;
	if(HitResult.PhysMaterial.IsValid() && Effects.Contains(HitResult.PhysMaterial.Get()))
	{
		Effect=Effects[HitResult.PhysMaterial.Get()];
	}
	if(!Effect)return;
	FRotator VFXRotation={0,0,0};
	if(PlayVFXByHitRotation)
		VFXRotation=HitResult.ImpactNormal.Rotation();
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Effect,HitResult.ImpactPoint,VFXRotation);
}

