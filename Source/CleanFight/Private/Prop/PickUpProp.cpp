

#include "Prop/PickUpProp.h" 

#include "Components/CapsuleComponent.h"

APickUpProp::APickUpProp()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>("CollisionComp");
	SetRootComponent(CollisionComp);
	SceneComp=CreateDefaultSubobject<USceneComponent>("SceneComp");
	SceneComp->SetupAttachment(CollisionComp);
	PropMesh=CreateDefaultSubobject<UStaticMeshComponent>("PropMesh");
	PropMesh->SetupAttachment(SceneComp);
	HighLightMesh=CreateDefaultSubobject<UStaticMeshComponent>("HighLightMesh");
	HighLightMesh->SetupAttachment(SceneComp);
}
 

void APickUpProp::OnPickUp_Implementation(ABaseCharacter* Character)
{
	if(!Character)return;
}

void APickUpProp::HighLightOn()
{
	if(HighLightMesh->IsVisible())return;
	HighLightMesh->SetVisibility(true);
}

void APickUpProp::HighLightOff()
{
	if(!HighLightMesh->IsVisible())return;
	HighLightMesh->SetVisibility(false);
}

void APickUpProp::BeginPlay()
{
	Super::BeginPlay();
	HighLightMesh->SetVisibility(false);
}
 
