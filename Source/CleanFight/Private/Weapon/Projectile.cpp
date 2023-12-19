

#include "Weapon/Projectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Component/HitVFXComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComp=CreateDefaultSubobject<USphereComponent>("CollisionComp");
	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	HitVfxComp=CreateDefaultSubobject<UHitVFXComponent>("HitVfxComp");
	
	SetRootComponent(CollisionComp);
	
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{ 
	if(Hit.bBlockingHit)
	{
		Hit.GetActor()->TakeDamage(ProjectileDamage, FDamageEvent(), nullptr, GetOwner());
		if(bExplore)
		{
			Explore();
		}
		else
		{
			HitVfxComp->PlayVFXOnHit(Hit); 
		}
	}
	Destroy();
}
 

void AProjectile::Explore()
{ 
	check(GetWorld());
	UGameplayStatics::ApplyRadialDamage(GetWorld(), ProjectileDamage, GetActorLocation(), ExploreRadius, DamageType, {},
	                                    this, nullptr, bDoFullDamage);
	CollisionComp->AddRadialImpulse(GetActorLocation(), ExploreRadius, ExploreRadius, ERadialImpulseFalloff::RIF_Linear,
	                                false);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ExploreVFX,GetActorLocation());
}
 
