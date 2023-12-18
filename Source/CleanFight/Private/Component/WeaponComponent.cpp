

#include "Component/WeaponComponent.h"

#include "Character/BaseCharacter.h"
#include "Prop/Weapon.h"

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

void UWeaponComponent::OnStartFire()
{
	if(!CurrentWeapon)return;
	
}

void UWeaponComponent::OnEndFire()
{
	
}

FTransform UWeaponComponent::GetWeaponSocketTransform() const
{
	const ABaseCharacter* Character= CastChecked<ABaseCharacter>(GetOwner());
	check(Character);
	return Character->GetMesh()->GetSocketTransform(WeaponSocketName);
}

void UWeaponComponent::GetAimLine(FVector& StartPoint, FVector& EndPoint)
{
	const AController* OwnerController=GetOwnerController();
	if(!OwnerController || !CurrentWeapon)return;

	FVector ViewLocation;
	FRotator ViewRotation;
	OwnerController->GetPlayerViewPoint(ViewLocation,ViewRotation);
	if(CurrentWeapon)
		StartPoint=CurrentWeapon.Get()->GetMuzzleLocation();
	EndPoint=ViewLocation+ViewRotation.Vector()*1000;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult,ViewLocation,EndPoint,ECC_Visibility,CollisionQueryParams);
	if(HitResult.bBlockingHit)
		EndPoint=HitResult.ImpactPoint;  
}

AController* UWeaponComponent::GetOwnerController()
{
	AController* Controller=Cast<AController>(GetOwner());
	return Controller;
}

