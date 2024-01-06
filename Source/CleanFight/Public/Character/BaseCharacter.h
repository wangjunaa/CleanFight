
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"  
#include "EnhancedInputSubsystems.h"  
#include "BaseCharacter.generated.h"
class UPlayerStateComponent;
class UHealthComponent;
class UWidgetComponent;
class UWeaponComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CLEANFIGHT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
	//基础组件
	UPROPERTY(VisibleAnywhere,Replicated,BlueprintReadWrite,Category="Comp")
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Comp")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(VisibleAnywhere,Replicated,BlueprintReadWrite,Category="Comp")
	TObjectPtr<UWeaponComponent> WeaponComponent;  
	UPROPERTY(VisibleAnywhere,Replicated,BlueprintReadWrite,Category="Comp")
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(VisibleAnywhere,Replicated,BlueprintReadWrite,Category="Comp")
	TObjectPtr<UPlayerStateComponent> PlayerStatComponent;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void BeginPlay() override;
	
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
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> CrouchAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> AimAction;
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> FireAction; 
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> NextWeaponAction; 
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> LastWeaponAction;
	UPROPERTY(EditAnywhere,Replicated,Category="Movement")
	float CrouchSpeed=50;
	UPROPERTY(EditAnywhere,Replicated,Category="Movement")
	float WalkSpeed=100;
	UPROPERTY(EditAnywhere,Replicated,Category="Movement")
	float RunSpeed=200;
	//判断是否在僵直
	UPROPERTY(Replicated)
	bool bStiffness=false; 
	//判断是否蹲下
	UPROPERTY(Replicated)
	bool bCrouch=false; 
	UPROPERTY(Replicated)
	bool bAiming=false;
	UPROPERTY(Replicated)
	bool bRunning=false;

	//输入绑定委托
	UFUNCTION(Server,Unreliable)
	void UpdateSpeed() const;  
	void Action_MoveForward(const FInputActionValue& Value);    
	void Action_MoveRight(const FInputActionValue& Value);  
	void Action_Jump(); 
	void Action_TurnAround(const FInputActionValue& Value); 
	void Action_LookUp(const FInputActionValue& Value);
	UFUNCTION(Server,Reliable)
	void Action_Running();
	UFUNCTION(Server,Reliable)
	void Action_EndRun();
	UFUNCTION(Server,Reliable)
	void Action_Crouch();
	UFUNCTION(Server,Reliable)
	void Action_EndCrouch(); 
	UFUNCTION(Server,Reliable,Category="Input")
	void Action_StartAim(); 
	UFUNCTION(Server,Reliable,Category="Input")
	void Action_EndAim();
	UFUNCTION(Server,Reliable,Category="Input")
	void Action_OnFire();
	UFUNCTION(Server,Reliable,Category="Input")
	void Action_OnEndFire();
	//调用计时器的速率
	const float AimScaleRate=0.01;
	//瞄准平滑放大时间
	float AimScaleTime=0.1;
	//瞄准平滑放大到的FOV值
	float AimScaleTargetValue=60;
	//瞄准正常FOV值
	float AimScaleNormalValue=90;
	//平滑缩放计时器
	FTimerHandle AimScaleTimeHandle;
	//视角放大
	void AimScaleAmplifier();
	//视角缩小
	void AimScaleReduce();
	FHitResult GetAimResult() const;

	UPROPERTY(Replicated)
	bool bIsFiring=false;

	UFUNCTION()
	virtual void OnDeath(AController* InstigatedBy) ;

	UPROPERTY(EditAnywhere,Category="Team")
	FName MyTeamName="Player";
public:	 

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
 
	UFUNCTION(BlueprintCallable,Category="Movement")
	bool IsRunning() const {return bRunning;} 
	UFUNCTION(BlueprintCallable,Category="State")
	bool IsStiff() const {return bStiffness;} 
	UFUNCTION(BlueprintCallable,Category="State")
	bool IsCrouch() const{return bCrouch;}
	UFUNCTION(BlueprintCallable,Category="State")
	bool IsAiming() const{return bAiming;} 
	UFUNCTION(BlueprintCallable,Category="State")
	bool IsFiring() const{return bIsFiring;};
	UFUNCTION(BlueprintCallable,Category="State")
	bool IsDeath() const;
	//硬直
	UFUNCTION(BlueprintCallable,Category="State")
	void StartStiffness() {bStiffness=true;} 
	UFUNCTION(BlueprintCallable,Category="State")
	void EndStiffness() {bStiffness=false;} 
	
	UFUNCTION(BlueprintCallable,Category="Movement")
	bool Can_Move() const {return !IsStiff();}
	UFUNCTION(BlueprintCallable,Category="Movement")
	bool Can_Run() const {return !IsStiff()&&!bCrouch ;}
	UFUNCTION(BlueprintCallable,Category="Movement")
	bool Can_Jump() const {return !IsStiff() && !bAiming && !bCrouch;};

	UFUNCTION(BlueprintCallable,Category="Team")
	FName GetTeamName()const {return MyTeamName;} 
	UFUNCTION(BlueprintCallable,Category="Team")
	bool IsTeamMate(FName TeamName) const {return TeamName==MyTeamName;}

	UFUNCTION(BlueprintCallable,Category="Experience")
	void AddExperience(int Amount);
	UFUNCTION(BlueprintCallable,Category="Experience")
	int GetLv()const{return Level;} 
	UFUNCTION(BlueprintCallable,Category="Experience")
	float GetExperiencePercent()const{return 1.0*ExperienceValue/GetMaxExperience();}
	UFUNCTION(BlueprintCallable,Category="Experience")
	int GetUpgradeNum()const{return UpgradeNum;}
	UFUNCTION(BlueprintCallable,Category="Experience")
	void OnUpgrade();
	UFUNCTION(BlueprintCallable,Category="StateUp")
	void AddMaxHealth(float Amount)const;
	UFUNCTION(BlueprintCallable,Category="StateUp")
	void AddHealValue(float Amount)const;
	UFUNCTION(BlueprintCallable,Category="StateUp")
	void AddRunningSpeed(float Amount);
	UFUNCTION(BlueprintCallable,Category="StateUp")
	void AddJumpNum();
	
private:
	
	int ExperienceValue=0;
	int Level=0;
	int GetMaxExperience() const;
	int UpgradeNum=0;
	UPROPERTY(EditAnywhere)
	int Experience=50;
};
