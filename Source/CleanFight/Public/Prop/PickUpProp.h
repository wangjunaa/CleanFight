#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpProp.generated.h"

<<<<<<< HEAD
class ABaseCharacter;
=======
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
class UCapsuleComponent;

UCLASS()
class CLEANFIGHT_API APickUpProp : public AActor
{
	GENERATED_BODY()
	
public:	
	APickUpProp();  
	UPROPERTY(VisibleAnywhere,Category="Comp")
<<<<<<< HEAD
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
=======
	TObjectPtr<UCapsuleComponent> CollisionComp;
	UFUNCTION(BlueprintCallable,Category="UI")
	UTexture2D* GetIcon()const{return Icon;}
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
	
protected:
	virtual void BeginPlay() override;
 
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTexture2D> Icon;
public:
	
};
