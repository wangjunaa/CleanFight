 
#include "BaseGameMode.h"

#include "Character/BaseCharacter.h"
#include "Character/BasePlayerController.h"

ABaseGameMode::ABaseGameMode()
{
	DefaultPawnClass=ABaseCharacter::StaticClass();
	PlayerControllerClass= ABasePlayerController::StaticClass();
}
