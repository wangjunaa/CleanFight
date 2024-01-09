

#include "Component/HealthComponent.h"

#include "Character/BaseCharacter.h" 

#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
	Health=MaxHealth;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay(); 
	SetHealth(MaxHealth);
	ABaseCharacter* Owner=Cast<ABaseCharacter>(GetOwner());
	if( GetOwnerRole()==ROLE_Authority && Owner){
		Owner->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::OnTakeAnyDamage); 
	}
	
}

void UHealthComponent::SetHealth(float NewHealth)
{
	if(GetOwnerRole()==ROLE_Authority)
	{ 
		Health=FMath::Clamp(NewHealth,0,MaxHealth);
	} 
	GEngine->AddOnScreenDebugMessage(01,1,FColor::Blue,L"生命变换");
	OnHealthChanged.Broadcast(Health);
}

void UHealthComponent::AddHealth(float Amount)
{
	SetHealth(Health+Amount);
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHealthComponent,Health);
	DOREPLIFETIME(UHealthComponent,MaxHealth);
	DOREPLIFETIME(UHealthComponent,HealValue);   
}

float UHealthComponent::GetHealthPercent() const
{
	return MaxHealth>0?Health/MaxHealth:0;
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, const float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(01,1,FColor::Blue,L"伤害");
	if(Damage<=0 || IsDeath())return; 
	SetHealth(Health-Damage);
	if(IsDeath())
		OnDeath.Broadcast(InstigatedBy);
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

 

