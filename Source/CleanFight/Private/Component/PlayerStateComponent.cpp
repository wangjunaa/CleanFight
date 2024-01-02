

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

void UPlayerStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
 