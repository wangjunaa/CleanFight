

<<<<<<< HEAD
#include "Prop/PickUpProp.h" 
=======
#include "Prop/PickUpProp.h"
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950

#include "Components/CapsuleComponent.h"

APickUpProp::APickUpProp()
{
	PrimaryActorTick.bCanEverTick = false;
	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>("CollisionComp");
	SetRootComponent(CollisionComp);
<<<<<<< HEAD
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
=======

>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
}

void APickUpProp::BeginPlay()
{
	Super::BeginPlay();
<<<<<<< HEAD
	HighLightMesh->SetVisibility(false);
=======
	
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
}
 
