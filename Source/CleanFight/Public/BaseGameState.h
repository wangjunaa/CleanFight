
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BaseGameState.generated.h"

class AWeapon;
class AAICharacter;

UCLASS()
class CLEANFIGHT_API ABaseGameState : public AGameState
{
	GENERATED_BODY()
public:
	ABaseGameState();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	FText GetPlayTime();
	UFUNCTION(BlueprintCallable)
	int GetDifficultLevel() const;
	UFUNCTION(BlueprintCallable)
	FString GetDifficultText()const;
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
	UPROPERTY(EditAnywhere)
	bool bSpawnEnemy=true;
};
