#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpProp.generated.h"

class ABaseCharacter;
class UCapsuleComponent;

UCLASS()
class CLEANFIGHT_API APickUpProp : public AActor
{
	GENERATED_BODY()
	
public:	
	APickUpProp();  
	UPROPERTY(VisibleAnywhere,Category="Comp")
	TObjectPtr<USceneComponent> SceneComp; 
	
	UPROPERTY(VisibleAnywhere,Category="Comp")
	TObjectPtr<UCapsuleComponent> CollisionComp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Prop")
	TObjectPtr<UStaticMeshComponent>PropMesh; 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Prop")
	TObjectPtr<UStaticMeshComponent>HighLightMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Prop")
	TSubclassOf<AActor>PropActorClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Prop")
	FText HintText;
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnPickUp(ABaseCharacter* Character);

	UFUNCTION(BlueprintCallable)
	void HighLightOn();
	UFUNCTION(BlueprintCallable)
	void HighLightOff();
	
protected:
	virtual void BeginPlay() override;
 
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTexture2D> Icon;
public:
	
};
