#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStateProp.generated.h"

class UCapsuleComponent;

UCLASS()
class CLEANFIGHT_API APlayerStateProp : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayerStateProp();  
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CollisionComp;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTexture2D> Icon;
protected:
	virtual void BeginPlay() override;
 
public:
	
};
