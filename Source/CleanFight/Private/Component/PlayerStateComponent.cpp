

#include "Component/PlayerStateComponent.h"
 

UPlayerStateComponent::UPlayerStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false; 

}

void UPlayerStateComponent::AddState(UTexture2D* Texture, int Num)
{
	PlayerState[Texture]+=Num;
}

TMap<UTexture2D*, int> UPlayerStateComponent::GetState()
{
	return PlayerState;
}

TArray<AWeaponModule*> UPlayerStateComponent::GetBag()const
{
	return Bag;
}

bool UPlayerStateComponent::AddToBag(AWeaponModule* WeaponModule, int Index)
{
	if(Bag.Num()>=MaxBagNum)return false;
	if(Index==-1)Bag.Add(WeaponModule);
	else Bag.Insert(WeaponModule,Index);
	return true;
}

bool UPlayerStateComponent::RemoveFromBag(AWeaponModule* WeaponModule, int Index)
{
	if(Index>=Bag.Num())return false;
	Bag.RemoveAt(Index);
	return true;
}

void UPlayerStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
 