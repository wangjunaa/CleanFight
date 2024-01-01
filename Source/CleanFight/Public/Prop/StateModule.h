// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StateModule.generated.h"

class ABaseCharacter;

UCLASS()
class CLEANFIGHT_API AStateModule : public AActor
{
	GENERATED_BODY()
	
public:	 
	AStateModule();
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UTexture2D>Icon;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText ModuleName;
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ExecuteModule(ABaseCharacter* Character);
protected: 
	virtual void BeginPlay() override;

public:	 

};
