
#include "BaseGameState.h"

<<<<<<< HEAD
#include "NavigationSystem.h"
#include "Character/AICharacter.h"
#include "Component/WeaponComponent.h"

=======
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
ABaseGameState::ABaseGameState()
{
	PrimaryActorTick.bCanEverTick=true;
}

void ABaseGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	PlayTime+=DeltaSeconds;
}

<<<<<<< HEAD
void ABaseGameState::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy();
}

=======
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
FText ABaseGameState::GetPlayTime()
{
	int Minute=PlayTime/60;
	int Second=int(PlayTime) % 60;
	if(Minute>=60)
	{
		return FText::FromString("∞");
	}
	FString MTime=FString::FromInt(Minute);
	for(int i=MTime.Len();i<2;i++) 
		MTime="0"+MTime; 
	FString STime=FString::FromInt(Second);
	for(int i=STime.Len();i<2;i++) 
		STime="0"+STime;
	return FText::FromString(MTime+":"+STime);
}

int ABaseGameState::GetDifficultLevel() const
{
	if(PlayTime<=10*60)  return 0; 
	if(PlayTime<=20*60) return 1;
	if(PlayTime<=30*60) return 2;
	if(PlayTime<=40*60) return 3;
	if(PlayTime<=50*60) return 4;
	if(PlayTime<=60*60) return 5;
	return 6;
	
}

FString ABaseGameState::GetDifficultText() const
{
	
	if(PlayTime<=10*60)  return L"轻松";
	if(PlayTime<=20*60) return	L"简单";
	if(PlayTime<=30*60) return	L"普通";
	if(PlayTime<=40*60) return	L"较难";
	if(PlayTime<=50*60) return	L"困难";
	if(PlayTime<=60*60) return	L"极难";
	return	L"史诗";
}
<<<<<<< HEAD

void ABaseGameState::SpawnEnemy()
{
	if(!GetWorld() || EnemyList.IsEmpty())return;
	const AController* Controller= Cast<AController>(GetWorld()->GetFirstPlayerController()); 
	if(!Controller)return;

	APawn* Pawn=Controller->GetPawn();
	if(!Pawn)return ;

	//获取当前导航信息
	const UNavigationSystemV1* NaviSystem= UNavigationSystemV1::GetCurrent(Pawn);
	if(!NaviSystem)return;
	FNavLocation NavLocation; 
	NaviSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), EnemySpawnRadius, NavLocation);
	const int Index=rand()%EnemyList.Num();
	const FTransform Transform={{0,0,0},NavLocation.Location};
	GetWorld()->SpawnActor<AAICharacter>(EnemyList[Index],Transform); 
	GetWorldTimerManager().SetTimer(EnemySpawnTimerHandle,this,&ABaseGameState::SpawnEnemy,GetEnemySpawnRate(),false);
}

float ABaseGameState::GetEnemySpawnRate() const
{
	return 30-GetDifficultLevel()*4;
}
=======
>>>>>>> bb3e997d8dd3414c71be7418da4129fd8e292950
