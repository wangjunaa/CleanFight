
#include "Prop/Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene=CreateDefaultSubobject<USceneComponent>("Scene");
	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


FVector AWeapon::GetMuzzleLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

