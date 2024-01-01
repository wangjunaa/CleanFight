

#include "Prop/StateModule.h"

AStateModule::AStateModule()
{
	PrimaryActorTick.bCanEverTick = false;

}
 

void AStateModule::ExecuteModule_Implementation(ABaseCharacter* Character)
{
	if(!Character)return;
}

void AStateModule::BeginPlay()
{
	Super::BeginPlay();
	
}
 

