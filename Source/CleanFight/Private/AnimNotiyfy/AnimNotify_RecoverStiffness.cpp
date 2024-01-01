
#include "AnimNotiyfy/AnimNotify_RecoverStiffness.h"
#include "AnimationUtils.h"
#include "Character/BaseCharacter.h"

void UAnimNotify_RecoverStiffness::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	
	if(ABaseCharacter* Character=Cast<ABaseCharacter>(MeshComp->GetOwner()))
	{
		UE_LOG(LogAnimNotify,Display,TEXT("恢复僵直"));
		Character->EndStiffness();
	}
}
