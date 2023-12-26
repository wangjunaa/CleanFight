#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpProp.generated.h"

class UCapsuleComponent;

UCLASS()
class CLEANFIGHT_API APickUpProp : public AActor
{
	GENERATED_BODY()
	
public:	
	APickUpProp();  
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CollisionComp;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTexture2D> Icon;
protected:
	virtual void BeginPlay() override;
 
public:
	
};
