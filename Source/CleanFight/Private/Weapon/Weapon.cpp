
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
	AProjectile* Projectile= GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass,{Rotator,Location});
	Projectile->SetActorScale3D({ProjectileScaleOffset,ProjectileScaleOffset,ProjectileScaleOffset});
	Projectile->ProjectileMovement.Get()->InitialSpeed+=ProjectileSpeedOffset;
	Projectile->ProjectileDamage+=ProjectileDamageOffset;
	Projectile->SetOwner(GetOwner());
	Projectile->FinishSpawning({Rotator,Location});
	Projectile->SetLifeSpan(5);
}

int AWeapon::GetMaxModuleNumber() const
{
	return MaxModuleNumber;
}

void AWeapon::SetMaxModuleNumber(int Value)
{
	MaxModuleNumber=Value;
	WeaponModules.SetNum(Value);
}

UMaterial* AWeapon::GetIcon() const
{
	return WeaponIcon;
}

TArray<AWeaponModule*> AWeapon::GetWeaponModules()const
{
	return WeaponModules;
}

bool AWeapon::AddModule(AWeaponModule* Module, int Index)
{ 
	if(Index==-1)
	{ 
		for (auto &Element : WeaponModules)
		{ 
			if(!Element)
			{ 
				Element=Module;
				if(Module)
					Module->ExecuteModule(this); 
				return true;
			}
		}
		return false;
	}
	RemoveModule(Index);
	WeaponModules[Index]=Module;
	if(Module) Module->ExecuteModule(this); 
	return true;
}
 

void AWeapon::ClearModule()
{
	for (auto &Element : WeaponModules)
	{
		Element=nullptr;
	}
}

bool AWeapon::RemoveModule(int Index)
{
	if(Index>=WeaponModules.Num() || !WeaponModules[Index])return false;
	WeaponModules[Index]->DeleteModule(this);
	WeaponModules[Index]=nullptr;
	
	return true;
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	SetMaxModuleNumber(5);
	for (const auto Module : WeaponModules)
	{
		if(Module) Module->ExecuteModule(this);
	}
}
 

FVector AWeapon::GetMuzzleLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

