
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponModule.generated.h"

class AWeapon;

UCLASS()
class CLEANFIGHT_API AWeaponModule : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponModule();
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetIcon() const;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category="UI")
	TObjectPtr<UTexture2D> Icon;
	UFUNCTION(BlueprintNativeEvent)
	void ExecuteModule(AWeapon* OwnerWeapon);
};
