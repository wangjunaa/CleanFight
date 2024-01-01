
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BaseGameState.generated.h"
<<<<<<< HEAD

class AWeapon;
class AAICharacter;

=======
 
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
UCLASS()
class CLEANFIGHT_API ABaseGameState : public AGameState
{
	GENERATED_BODY()
public:
	ABaseGameState();
	virtual void Tick(float DeltaSeconds) override;
<<<<<<< HEAD
	virtual void BeginPlay() override;
=======
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
	UFUNCTION(BlueprintCallable)
	FText GetPlayTime();
	UFUNCTION(BlueprintCallable)
	int GetDifficultLevel() const;
	UFUNCTION(BlueprintCallable)
	FString GetDifficultText()const;
<<<<<<< HEAD
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AAICharacter>>EnemyList; 
private:
	float PlayTime=0;
	int DifficultLevel=0;
	UPROPERTY(EditAnywhere)
	float EnemySpawnRadius=1000;
	float GetEnemySpawnRate() const;
	FTimerHandle EnemySpawnTimerHandle;
=======
private:
	float PlayTime=0;
	int DifficultLevel=0;
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
};
