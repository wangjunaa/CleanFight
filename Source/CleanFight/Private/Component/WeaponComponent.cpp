

#include "Component/WeaponComponent.h"

#include "Character/BaseCharacter.h"  
#include "Weapon/Weapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComp,All,All);
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnWeapon();
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}
 

TSubclassOf<AWeapon> UWeaponComponent::GetCurrentWeaponClass()
{
	if(WeaponList.Num()==0)return nullptr;
	return WeaponList[CurrentWeaponIndex];
}

void UWeaponComponent::OnStartFire()
{
	if(!GetCurrentWeapon())return;
	const float FireRate=GetCurrentWeapon()->GetFireRate();
	check(GetWorld());
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &UWeaponComponent::MakeShoot, FireRate, true, 0);
	Firing=true;
}

void UWeaponComponent::MakeShoot() const
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
	Firing=false;
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

void UWeaponComponent::SpawnWeapon()
{
	if(!GetCurrentWeaponClass())return;
	const ABaseCharacter* Character=Cast<ABaseCharacter>(GetOwner());
	const FTransform WeaponTransform= Character->GetMesh()->GetSocketTransform(WeaponSocketName);
	check(GetWorld());

	UE_LOG(LogWeaponComp,Display,TEXT("生成武器"));
	CurrentWeapon= GetWorld()->SpawnActor<AWeapon>(GetCurrentWeaponClass(),WeaponTransform);
	CurrentWeapon->AttachToComponent(Character->GetMesh(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,false),WeaponSocketName);
}

