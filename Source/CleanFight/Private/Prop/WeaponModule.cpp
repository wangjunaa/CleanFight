

#include "Prop/WeaponModule.h"

AWeaponModule::AWeaponModule()
{
	PrimaryActorTick.bCanEverTick = true;

}

UTexture2D* AWeaponModule::GetIcon() const
{
	return Icon;
}

void AWeaponModule::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponModule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);    

}

void AWeaponModule::ExecuteModule_Implementation(AWeapon* OwnerWeapon)
{
	if(!OwnerWeapon)return;
}
 
 

