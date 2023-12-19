

#include "Component/WeaponComponent.h"

#include "Character/BaseCharacter.h" 
#include "Weapon/Weapon.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();	
}

 

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

AWeapon* UWeaponComponent::GetCurrentWeapon()
{
	if(WeaponList.Num()==0)return nullptr;
	return WeaponList[CurrentWeaponIndex];
}

void UWeaponComponent::OnStartFire()
{
	if(!GetCurrentWeapon())return;
	float FireRate=GetCurrentWeapon()->GetFireRate();
	check(GetWorld());
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle,this,&UWeaponComponent::MakeShoot,FireRate,true);
}

void UWeaponComponent::MakeShoot()
{
	FVector TargetPoint;
	GetAimLine(TargetPoint);
	GetCurrentWeapon()->MakeShoot(TargetPoint);
}

void UWeaponComponent::OnEndFire()
{ 
	if(!GetCurrentWeapon())return;
	check(GetWorld());
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

FTransform UWeaponComponent::GetWeaponSocketTransform() const
{
	const ABaseCharacter* Character= CastChecked<ABaseCharacter>(GetOwner());
	check(Character);
	return Character->GetMesh()->GetSocketTransform(WeaponSocketName);
}

void UWeaponComponent::GetAimLine(FVector& TargetPoint) const
{
	const AController* OwnerController=GetOwnerController();
	if(!OwnerController)return;

	FVector ViewLocation;
	FRotator ViewRotation;
	OwnerController->GetPlayerViewPoint(ViewLocation,ViewRotation);
 
	TargetPoint=ViewLocation+ViewRotation.Vector()*1000;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult,ViewLocation,TargetPoint,ECC_Visibility,CollisionQueryParams);
	if(HitResult.bBlockingHit)
		TargetPoint=HitResult.ImpactPoint; 
}


AController* UWeaponComponent::GetOwnerController() const
{
	AController* Controller=Cast<AController>(GetOwner());
	return Controller;
}

