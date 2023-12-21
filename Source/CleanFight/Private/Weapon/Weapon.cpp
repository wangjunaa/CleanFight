
#include "Weapon/Weapon.h"

#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Projectile.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene=CreateDefaultSubobject<USceneComponent>("Scene");
	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");

	WeaponMesh->SetupAttachment(Scene);
}
 
void AWeapon::MakeShoot(const FVector& TargetPoint) const
{
	const FVector Location=GetMuzzleLocation();
	const FRotator Rotator=UKismetMathLibrary::FindLookAtRotation(Location,TargetPoint); 
	check(GetWorld());
	const auto Projectile= GetWorld()->SpawnActor<AProjectile>(ProjectileClass,Location,Rotator);
	Projectile->SetOwner(GetOwner());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay(); 
}
 

FVector AWeapon::GetMuzzleLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

