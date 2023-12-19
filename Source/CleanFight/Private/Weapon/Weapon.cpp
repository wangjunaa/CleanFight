
#include "Weapon/Weapon.h"

#include "Kismet/KismetMathLibrary.h"
#include "Weapon/Projectile.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene=CreateDefaultSubobject<USceneComponent>("Scene");
	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
}
 
void AWeapon::MakeShoot(FVector TargetPoint)
{ 
	FVector Location=GetMuzzleLocation();
	FRotator Rotator=UKismetMathLibrary::FindLookAtRotation(Location,TargetPoint);
	FTransform ProjectileTransform=FTransform(Rotator,Location);
	check(GetWorld());
	GetWorld()->SpawnActor<AProjectile>(Location,Rotator);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}
 

FVector AWeapon::GetMuzzleLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

