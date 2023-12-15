#include "Character/BaseCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" 
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter,All,All)
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	//创建组件
	CameraComponent=CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	 
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	//设置
	GetCapsuleComponent()->SetCapsuleHalfHeight(10);
	GetCapsuleComponent()->SetCapsuleRadius(4);
	
	GetMesh()->SetRelativeLocation({0,0,-10});
	GetMesh()->SetRelativeRotation({0,0,-90});

	//设置运动属性
	if(UCharacterMovementComponent* CharacterMovementComponent=GetCharacterMovement())
	{
		CharacterMovementComponent->MaxWalkSpeed=WalkSpeed;
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定输入到角色控制
	if(APlayerController* PC = CastChecked<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	//绑定输入按键
	if(UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(MoveForwardAction)
		{
			EnhancedInputComponent->BindAction(MoveForwardAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Action_MoveForward);
		}
		if(MoveRightAction)
		{
			EnhancedInputComponent->BindAction(MoveRightAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Action_MoveRight);
		}
		if(JumpAction)
		{
			//UE_LOG(LogBaseCharacter,Warning,TEXT("绑定跳跃"));
			EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&ABaseCharacter::Action_Jump);
		} 
		if(TurnAroundAction)
		{
			EnhancedInputComponent->BindAction(TurnAroundAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Action_TurnAround);
		} 
		if(LookUpAction)
		{
			EnhancedInputComponent->BindAction(LookUpAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Action_LookUp);
		} 
		if(RunAction)
		{
			EnhancedInputComponent->BindAction(RunAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Action_Running);
			EnhancedInputComponent->BindAction(RunAction,ETriggerEvent::Completed,this,&ABaseCharacter::Action_EndRun);
		}
	}
}

void ABaseCharacter::Action_MoveForward(const FInputActionValue& Value)
{
	if(IsStiff())return;

	UE_LOG(LogBaseCharacter,Display,TEXT("MoveForward"));
	AddMovementInput(CameraComponent->GetForwardVector(),Value.Get<float>());
}

void ABaseCharacter::Action_MoveRight(const FInputActionValue& Value)
{
	if(IsStiff())return;

	UE_LOG(LogBaseCharacter,Display,TEXT("MoveRight"));
	AddMovementInput(CameraComponent->GetRightVector(),Value.Get<float>());
	
}

void ABaseCharacter::Action_Jump()
{
	if(IsStiff())return;
	UE_LOG(LogBaseCharacter,Display,TEXT("Jump"));
	Jump();
}

void ABaseCharacter::Action_TurnAround(const FInputActionValue& Value)
{
	UE_LOG(LogBaseCharacter,Display,TEXT("TurnAround"));
	AddControllerYawInput(Value.Get<float>());
}

void ABaseCharacter::Action_LookUp(const FInputActionValue& Value)
{
	UE_LOG(LogBaseCharacter,Display,TEXT("LookUp"));
	AddControllerPitchInput(Value.Get<float>());
}

void ABaseCharacter::Action_Running()
{ 
	if(IsStiff())return;
	UE_LOG(LogBaseCharacter,Display,TEXT("StartRun"));
	check(GetCharacterMovement()); 
	GetCharacterMovement()->MaxWalkSpeed=RunSpeed;
	AddMovementInput(CameraComponent->GetForwardVector());
	Running=true;
}

void ABaseCharacter::Action_EndRun()
{
	UE_LOG(LogBaseCharacter,Display,TEXT("EndRun")); 
	check(GetCharacterMovement()); 
	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
	Running=false;
}

