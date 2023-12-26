
#include "BaseGameState.h"

ABaseGameState::ABaseGameState()
{
	PrimaryActorTick.bCanEverTick=true;
}

void ABaseGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	PlayTime+=DeltaSeconds;
}

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
