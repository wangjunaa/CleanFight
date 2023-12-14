
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CLEANFIGHT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	//基础组件
	UPROPERTY(VisibleAnywhere,Category="Comp")
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere,Category="Comp")
	USpringArmComponent* SpringArmComponent;
	
	
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//增强输入
	UPROPERTY(EditAnywhere,Category="Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* MoveForwardAction; 
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* MoveRightAction;
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* JumpAction;
	
};
