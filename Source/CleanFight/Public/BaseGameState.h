
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BaseGameState.generated.h"
 
UCLASS()
class CLEANFIGHT_API ABaseGameState : public AGameState
{
	GENERATED_BODY()
public:
	ABaseGameState();
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable)
	FText GetPlayTime();
	UFUNCTION(BlueprintCallable)
	int GetDifficultLevel() const;
	UFUNCTION(BlueprintCallable)
	FString GetDifficultText()const;
private:
	float PlayTime=0;
	int DifficultLevel=0;
};
