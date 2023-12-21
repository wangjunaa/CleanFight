#include "Character/BaseCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"  
#include "Camera/CameraComponent.h"
#include "Component/WeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "GameFramework/SpringArmComponent.h"
DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter,All,All)
ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	//创建组件
	CameraComponent=CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	WeaponComponent=CreateDefaultSubobject<UWeaponComponent>("WeaponComp");
	
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);

	
	//设置
	GetCapsuleComponent()->SetCapsuleHalfHeight(18);
	GetCapsuleComponent()->SetCapsuleRadius(8);
	
	GetMesh()->SetRelativeLocation({0,0,-10});
	GetMesh()->SetRelativeRotation({0,-90,0});
	GetMesh()->SetRelativeScale3D({2,2,2});

	CameraComponent->SetFieldOfView(AimScaleNormalValue);
	
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
		if(CrouchAction)
		{
			EnhancedInputComponent->BindAction(CrouchAction,ETriggerEvent::Started,this,&ABaseCharacter::Action_Crouch);
			EnhancedInputComponent->BindAction(CrouchAction,ETriggerEvent::Completed,this,&ABaseCharacter::Action_EndCrouch); 
		}
		if(AimAction)
		{
			EnhancedInputComponent->BindAction(AimAction,ETriggerEvent::Started,this,&ABaseCharacter::Action_StartAim);
			EnhancedInputComponent->BindAction(AimAction,ETriggerEvent::Completed,this,&ABaseCharacter::Action_EndAim);
		}
		if(FireAction) 
		{
			check(WeaponComponent);
			EnhancedInputComponent->BindAction(FireAction,ETriggerEvent::Started,WeaponComponent.Get(),&UWeaponComponent::OnStartFire);
			EnhancedInputComponent->BindAction(FireAction,ETriggerEvent::Completed,WeaponComponent.Get(),&UWeaponComponent::OnEndFire);
		}
	}
}

void ABaseCharacter::Action_MoveForward(const FInputActionValue& Value)
{
	if(!Can_Move())return; 
	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
	UE_LOG(LogBaseCharacter,Display,TEXT("前后移动"));
	AddMovementInput(CameraComponent->GetForwardVector(),Value.Get<float>());
}

void ABaseCharacter::Action_MoveRight(const FInputActionValue& Value)
{
	if(!Can_Move())return;

	UE_LOG(LogBaseCharacter,Display,TEXT("左右移动"));
	AddMovementInput(CameraComponent->GetRightVector(),Value.Get<float>());
	
}

void ABaseCharacter::Action_Jump()
{
	if(!Can_Jump())return;
	UE_LOG(LogBaseCharacter,Display,TEXT("跳跃"));
	Jump();
}

void ABaseCharacter::Action_TurnAround(const FInputActionValue& Value)
{
	UE_LOG(LogBaseCharacter,Display,TEXT("左右视角移动"));
	AddControllerYawInput(Value.Get<float>());
}

void ABaseCharacter::Action_LookUp(const FInputActionValue& Value)
{
	UE_LOG(LogBaseCharacter,Display,TEXT("上下视角移动"));
	AddControllerPitchInput(Value.Get<float>());
}

void ABaseCharacter::Action_Running()
{
	if(!Can_Run())return;
	GetCharacterMovement()->MaxWalkSpeed=RunSpeed;
	//瞄准时不奔跑
	if(IsAiming())
	{
		Action_MoveForward(1);
		return; 
	} 
	if(!Running)
	{
		UE_LOG(LogBaseCharacter,Display,TEXT("开始奔跑"));
		check(GetCharacterMovement());
		Running=true; 
	}
	AddMovementInput(CameraComponent->GetForwardVector());
}

void ABaseCharacter::Action_EndRun()
{
	UE_LOG(LogBaseCharacter,Display,TEXT("结束奔跑")); 
	check(GetCharacterMovement()); 
	Running=false;
}

void ABaseCharacter::Action_Crouch()
{
	if(IsStiff() || IsRunning())return;
	UE_LOG(LogBaseCharacter,Display,TEXT("蹲下")); 
	Crouch=true;
	check(GetCharacterMovement());
	GetCharacterMovement()->MaxWalkSpeed=CrouchSpeed;
}

void ABaseCharacter::Action_EndCrouch()
{
	UE_LOG(LogBaseCharacter,Display,TEXT("起身")); 
	Crouch=false; 
	check(GetCharacterMovement());
	GetCharacterMovement()->MaxWalkSpeed=WalkSpeed; 
}

void ABaseCharacter::Action_StartAim()
{
	check(CameraComponent);
	check(GetWorld());
	GetWorldTimerManager().SetTimer(AimScaleTimeHandle, this, &ABaseCharacter::AimScaleAmplifier, AimScaleRate, true);
	GetController()->GetPawn()->bUseControllerRotationYaw=true;
	Aiming=true;
}

void ABaseCharacter::Action_EndAim()
{
	check(CameraComponent);
	check(GetWorld());  
	GetWorldTimerManager().SetTimer(AimScaleTimeHandle,this,&ABaseCharacter::AimScaleReduce,AimScaleRate,true);
	GetController()->GetPawn()->bUseControllerRotationYaw=false;
	Aiming=false;
}
 

void ABaseCharacter::AimScaleAmplifier()
{
	//每次放大多少
	float ScaleValue=(AimScaleNormalValue-AimScaleTargetValue)/(AimScaleTime/AimScaleRate);
	CameraComponent->SetFieldOfView(CameraComponent->FieldOfView-ScaleValue);
	if(CameraComponent->FieldOfView<=AimScaleTargetValue)
	{
		UE_LOG(LogBaseCharacter,Display,TEXT("视角放大完成"));
		GetWorldTimerManager().ClearTimer(AimScaleTimeHandle);
	}
}

void ABaseCharacter::AimScaleReduce()
{ 
	//每次缩小多少
	float ScaleValue=(AimScaleNormalValue-AimScaleTargetValue)/(AimScaleTime/AimScaleRate);
	CameraComponent->SetFieldOfView(CameraComponent->FieldOfView+ScaleValue);
	if(CameraComponent->FieldOfView>=AimScaleNormalValue)
	{
		UE_LOG(LogBaseCharacter,Display,TEXT("视角缩小完成"));
		GetWorldTimerManager().ClearTimer(AimScaleTimeHandle);
	}
}


FHitResult ABaseCharacter::GetAimResult()
{
	const AController* OwnerController=GetController();
	if(!OwnerController)return {};

	FVector ViewLocation;
	FRotator ViewRotation;
	OwnerController->GetPlayerViewPoint(ViewLocation,ViewRotation); 
	FVector EndPoint=ViewLocation+ViewRotation.Vector()*1000;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult,ViewLocation,EndPoint,ECC_Visibility,CollisionQueryParams);
	return HitResult;
}
