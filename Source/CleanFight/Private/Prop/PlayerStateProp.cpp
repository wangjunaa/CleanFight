

#include "Prop/PlayerStateProp.h"

#include "Components/CapsuleComponent.h"

APlayerStateProp::APlayerStateProp()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>("CollisionComp");
	SetRootComponent(CollisionComp);

}

void APlayerStateProp::BeginPlay()
{
	Super::BeginPlay();
	
}
 
