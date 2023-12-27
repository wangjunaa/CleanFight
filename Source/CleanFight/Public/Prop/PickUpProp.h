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
	UPROPERTY(VisibleAnywhere,Category="Comp")
	TObjectPtr<UCapsuleComponent> CollisionComp;
	UFUNCTION(BlueprintCallable,Category="UI")
	UTexture2D* GetIcon()const{return Icon;}
	
protected:
	virtual void BeginPlay() override;
 
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTexture2D> Icon;
public:
	
};
