
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"  
#include "EnhancedInputSubsystems.h"  
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
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere,Category="Comp")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	
	//增强输入
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveForwardAction; 
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveRightAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> JumpAction; 
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> TurnAroundAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> LookUpAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> RunAction;
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
 
	UFUNCTION(BlueprintCallable,Category="Movement")
	bool IsRunning() const {return Running;}

	//硬直
	UFUNCTION(BlueprintCallable,Category="State")
	void StartStiffness() {Stiffness=true;} 
	UFUNCTION(BlueprintCallable,Category="State")
	void EndStiffness() {Stiffness=false;} 
	UFUNCTION(BlueprintCallable,Category="State")
	bool IsStiff() {return Stiffness;}
private:
	UPROPERTY(EditAnywhere,Category="Movement")
	float WalkSpeed=100;
	UPROPERTY(EditAnywhere,Category="Movement")
	float RunSpeed=200;

	bool Stiffness=false;
	//判断是否在奔跑
	bool Running=false;
	
	void Action_MoveForward(const FInputActionValue& Value); 
	void Action_MoveRight(const FInputActionValue& Value);  
	void Action_Jump();
	void Action_TurnAround(const FInputActionValue& Value);
	void Action_LookUp(const FInputActionValue& Value);
	void Action_Running();
	void Action_EndRun();
};
