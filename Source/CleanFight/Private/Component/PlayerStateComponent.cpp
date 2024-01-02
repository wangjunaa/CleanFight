

#include "Component/PlayerStateComponent.h"
 

UPlayerStateComponent::UPlayerStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false; 
}

void UPlayerStateComponent::AddState(UTexture2D* Texture, int Num)
{
	if(PlayerState.Contains(Texture))
		PlayerState[Texture]+=Num;
	else PlayerState.Add(Texture,Num);
}

TMap<UTexture2D*, int> UPlayerStateComponent::GetState()
{
	return PlayerState;
}

void UPlayerStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
 