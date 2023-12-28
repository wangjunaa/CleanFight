#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeath,AController*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged,int)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLEANFIGHT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	virtual void BeginPlay() override;
 
	UFUNCTION(BlueprintCallable,Category="Health")
	float GetHealth()const{return Health;}
	UFUNCTION(BlueprintCallable,Category="Health")
	float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable,Category="Health")
	bool IsDeath() const {return FMath::IsNearlyZero(Health);} 
	UFUNCTION(BlueprintCallable,Category="Health")
	void SetHealth(float NewHealth);
	UFUNCTION(BlueprintCallable,Category="Health")
	void AddHealth(float Amount);

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
	
private: 
	FTimerHandle HealTimerHandle;
	
	float Health;
	UPROPERTY(EditDefaultsOnly,Category="Health",meta=(ClampMin=0)) 
	float MaxHealth=100;
	UPROPERTY(EditAnywhere,Category="Health|Heal")
	bool AutoHeal=true;
	UPROPERTY(EditAnywhere,Category="Health|Heal",meta=(EditCondition="AutoHeal"))
	float HealValue=0.01;
	UPROPERTY(EditAnywhere,Category="Health|Heal",meta=(EditCondition="AutoHeal"))
	float HealUpdateTime=0.01;
	UPROPERTY(EditAnywhere,Category="Health|Heal",meta=(EditCondition="AutoHeal"))
	float HealDelay=3;

	UFUNCTION()//CNM委托记得加这个
	void OnTakeAnyDamage( AActor* DamagedActor, float Damage, const  UDamageType* DamageType,  AController* InstigatedBy, AActor* DamageCauser);
	
	void HealUpdate();
	
};
