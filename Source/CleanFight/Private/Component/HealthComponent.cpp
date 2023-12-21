

#include "Component/HealthComponent.h"
 
UHealthComponent::UHealthComponent()
{ 
	PrimaryComponentTick.bCanEverTick = false;
	Health=MaxHealth;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay(); 
	if(AActor* Owner=GetOwner()){
		Owner->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::OnTakeAnyDamage);
	}
	SetHealth(MaxHealth);
	
}

void UHealthComponent::SetHealth(float NewHealth)
{ 
	Health=FMath::Clamp(NewHealth,0,MaxHealth);
	OnHealthChanged.ExecuteIfBound(Health);
}

void UHealthComponent::AddHealth(float Amount)
{
	SetHealth(Health+Amount);
}

float UHealthComponent::GetHealthPercent() const
{
	return MaxHealth>0?Health/MaxHealth:0;
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	
	if(Damage<=0 || IsDeath())return; 
	SetHealth(Health-Damage);
	if(IsDeath())
		OnDeath.ExecuteIfBound();
	else  if(Health<MaxHealth && GetWorld() && AutoHeal)
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this,&UHealthComponent::HealUpdate,HealUpdateTime,true,HealDelay);
	}
}

void UHealthComponent::HealUpdate()
{ 
	if(IsDeath())return;
	SetHealth(Health+HealValue);
	if(FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	} 
}

 

