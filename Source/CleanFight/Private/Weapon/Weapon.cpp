
#include "Weapon/Weapon.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Prop/WeaponModule.h"
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
	AProjectile* Projectile= GetWorld()->SpawnActor<AProjectile>(ProjectileClass,Location,Rotator);
	Projectile->SetActorScale3D({ProjectileScaleOffset,ProjectileScaleOffset,ProjectileScaleOffset});
	Projectile->ProjectileMovement.Get()->InitialSpeed+=ProjectileSpeedOffset;
	Projectile->ProjectileDamage+=ProjectileDamageOffset;
	Projectile->SetOwner(GetOwner()); 
}

int AWeapon::GetMaxModuleNumber() const
{
	return MaxModuleNumber;
}

UMaterial* AWeapon::GetIcon() const
{
	return WeaponIcon;
}

TArray<AWeaponModule*> AWeapon::GetWeaponModules()const
{
	return WeaponModules;
}

bool AWeapon::AddModule(AWeaponModule* Module)
{
	if(WeaponModules.Num()>=MaxModuleNumber)return false;
	WeaponModules.Add(Module);
	Module->ExecuteModule(this);
	return true;
}

bool AWeapon::RemoveModule(int Index)
{
	if(Index>=WeaponModules.Num())return false;
	WeaponModules[Index]->DeleteModule(this);
	WeaponModules.RemoveAt(Index);
	
	return true;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	for (const auto Module : WeaponModules)
	{
		Module->ExecuteModule(this);
	}
}
 

FVector AWeapon::GetMuzzleLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

