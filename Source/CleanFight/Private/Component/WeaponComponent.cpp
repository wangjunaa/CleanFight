

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

AWeapon* UWeaponComponent::GetCurrentWeapon() const
{
	if(CurrentWeaponIndex>=WeaponList.Num())return nullptr;
	return WeaponList[CurrentWeaponIndex];
}

TArray<AWeapon*> UWeaponComponent::GetWeaponList()const
{
	return WeaponList;
}


UMaterial* UWeaponComponent::GetCurrentWeaponIcon() const
{
	if(GetCurrentWeapon())
	{
		return GetCurrentWeapon()->GetIcon();
	}
	return nullptr;
}

void UWeaponComponent::Fire()
{
	if(!GetCurrentWeapon() || bFireInCD)return;
	check(GetWorld());
	MakeShoot();   
}
 
void UWeaponComponent::MakeShoot()
{
	UE_LOG(LogWeaponComp,Display,TEXT("开火"));
	//射击逻辑
	bFireInCD=true;
	const FVector TargetPoint=GetFireTargetPoint(); 
	GetCurrentWeapon()->MakeShoot(TargetPoint);
 
	//射击cd 
	const float FireRate=GetCurrentWeapon()->GetFireRate();
	GetWorld()->GetTimerManager().SetTimer(FireCDTimerHandle, this,&UWeaponComponent::FireCDFinish,FireRate,false,FireRate);
}

bool UWeaponComponent::AddWeapon(AWeapon* NewWeapon)
{
	if(WeaponList.Num()>=MaxWeaponNumber)return false;
	WeaponList.Add(NewWeapon);
	const ABaseCharacter* Character=Cast<ABaseCharacter>(GetOwner());
	NewWeapon->AttachToComponent(Character->GetMesh(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,false),WeaponSocketName);
	NewWeapon->SetOwner(GetOwner());
	if(WeaponList.Num()>1)
		NewWeapon->SetVisibility(false); 
	return true;
}

FTransform UWeaponComponent::GetWeaponSocketTransform() const
{
	const ABaseCharacter* Character= Cast<ABaseCharacter>(GetOwner());
	check(Character);
	return Character->GetMesh()->GetSocketTransform(WeaponSocketName);
}

FVector UWeaponComponent::GetFireTargetPoint() const
{ 
	const ABaseCharacter* Character=Cast<ABaseCharacter>(GetOwner());
	if(Character->IsAiming()) 
		return GetAimPoint();
	return Character->GetActorForwardVector()*FireRange+Character->GetActorLocation();
}

FVector UWeaponComponent::GetAimPoint() const
{
	const AController* OwnerController=GetOwnerController();
	if(!OwnerController)return{};

	FVector ViewLocation;
	FRotator ViewRotation;
	OwnerController->GetPlayerViewPoint(ViewLocation,ViewRotation);
 
	FVector TargetPoint=ViewLocation+ViewRotation.Vector()*FireRange;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult,ViewLocation,TargetPoint,ECC_Visibility,CollisionQueryParams);
	if(HitResult.bBlockingHit)
		TargetPoint=HitResult.ImpactPoint;
	return TargetPoint;
}


AController* UWeaponComponent::GetOwnerController() const
{
	const ABaseCharacter* Owner=Cast<ABaseCharacter>(GetOwner());
	return Owner->GetController();
}

void UWeaponComponent::SpawnWeapon()
{
	if(DefaultWeaponClassList.Num()==0)return;
	const ABaseCharacter* Character=Cast<ABaseCharacter>(GetOwner());
	const FTransform WeaponTransform= Character->GetMesh()->GetSocketTransform(WeaponSocketName);
	check(GetWorld());

	UE_LOG(LogWeaponComp,Display,TEXT("生成武器"));
	for (auto Element : DefaultWeaponClassList)
	{ 
		AWeapon* Weapon= GetWorld()->SpawnActor<AWeapon>(Element,WeaponTransform); 
		Weapon->AttachToComponent(Character->GetMesh(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,false),WeaponSocketName);
		Weapon->SetOwner(GetOwner());
		Weapon->SetVisibility(false); 
		WeaponList.Add(Weapon);
	}
	if(GetCurrentWeapon())
	{
		GetCurrentWeapon()->SetVisibility(true);
	}
}

