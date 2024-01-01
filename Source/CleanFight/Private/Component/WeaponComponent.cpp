

#include "Component/WeaponComponent.h"

#include "NiagaraFunctionLibrary.h"
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
	ModuleBag.SetNum(MaxBagNum); 
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

int UWeaponComponent::GetCurrentWeaponIndex() const
{
	if (WeaponList.Num())
	{
		return CurrentWeaponIndex+1;
	}
	return 0;
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
	if(WeaponList.Num()>=MaxWeaponNumber || !NewWeapon)return false;
	WeaponList.Add(NewWeapon);
	const ABaseCharacter* Character=Cast<ABaseCharacter>(GetOwner());
	NewWeapon->AttachToComponent(Character->GetMesh(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,false),WeaponSocketName);
	NewWeapon->SetOwner(GetOwner());
	if(WeaponList.Num()>1)
		NewWeapon->SetVisibility(false); 
	return true;
}

bool UWeaponComponent::RemoveWeapon(int Index)
{
	if(Index>=WeaponList.Num())return false;
	WeaponList[Index]->Destroy();
	WeaponList.RemoveAt(Index);
	NextWeapon();
	LastWeapon();
	return true; 
}

void UWeaponComponent::NextWeapon()
{
	if(WeaponList.Num()==0 || !GetCurrentWeapon())return;
	GetCurrentWeapon()->SetVisibility(false);
	CurrentWeaponIndex=(CurrentWeaponIndex+1)%WeaponList.Num();
	GetCurrentWeapon()->SetVisibility(true);
	if(SwitchWeaponVfx)
	{ 
		const auto Location=GetCurrentWeapon()->GetActorLocation();
		const auto Rotator=GetCurrentWeapon()->GetActorRotation();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),SwitchWeaponVfx,Location,Rotator);
	}
}
  
void UWeaponComponent::LastWeapon()
{
	if(WeaponList.Num()==0 || !GetCurrentWeapon())return;
	GetCurrentWeapon()->SetVisibility(false);
	CurrentWeaponIndex=(CurrentWeaponIndex+WeaponList.Num()-1)%WeaponList.Num();
	GetCurrentWeapon()->SetVisibility(true);
	
	if(SwitchWeaponVfx)
	{
		const auto Location=GetCurrentWeapon()->GetActorLocation();
		const auto Rotator=GetCurrentWeapon()->GetActorRotation();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),SwitchWeaponVfx,Location,Rotator);
	}
}

TArray<AWeaponModule*> UWeaponComponent::GetModuleBag() const
{
	return ModuleBag;
}

 

bool UWeaponComponent::AddToBag(AWeaponModule* WeaponModule, int Index)
{ 
	if(Index==-1)
	{
		for (auto &Element : ModuleBag)
		{
			if(!Element)
			{
				Element=WeaponModule;
				return true;
			}
		}
		return  false;
	}
	ModuleBag[Index]=WeaponModule;
	return true;
}

void UWeaponComponent::ClearBag()
{
	ModuleBag.Empty();
}

bool UWeaponComponent::RemoveFromBag( int Index)
{
	if(Index>=ModuleBag.Num())return false;
	ModuleBag[Index]=nullptr;
	return true;
}

int UWeaponComponent::GetMaxBagNum() const
{
	return MaxBagNum;
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

