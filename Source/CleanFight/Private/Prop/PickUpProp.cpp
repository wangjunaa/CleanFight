

#include "Prop/PickUpProp.h"

#include "Components/CapsuleComponent.h"

APickUpProp::APickUpProp()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>("CollisionComp");
	SetRootComponent(CollisionComp);

}

void APickUpProp::BeginPlay()
{
	Super::BeginPlay();
	
}
 
