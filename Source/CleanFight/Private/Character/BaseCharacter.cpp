#include "Character/BaseCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"   
#include "Camera/CameraComponent.h" 
#include "Component/HealthComponent.h"
#include "Component/PlayerStateComponent.h" 
#include "Component/WeaponComponent.h"
#include "Components/CapsuleComponent.h"  
#include "GameFramework/CharacterMovementComponent.h" 
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Weapon/Weapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All)

ABaseCharacter::ABaseCharacter()
{ 
	bReplicates=true;
	PrimaryActorTick.bCanEverTick = false;
	//创建组件
	CameraComponent=CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	WeaponComponent=CreateDefaultSubobject<UWeaponComponent>("WeaponComp"); 
	HealthComponent=CreateDefaultSubobject<UHealthComponent>("HealthComp");
	PlayerStatComponent=CreateDefaultSubobject<UPlayerStateComponent>("PlayerStateComp");
	
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(SpringArmComponent); 
	
	//设置
	if(GetCapsuleComponent())
	{ 
		GetCapsuleComponent()->SetCapsuleHalfHeight(18);
		GetCapsuleComponent()->SetCapsuleRadius(8);
	}
	if(GetMesh())
	{ 
		GetMesh()->SetRelativeLocation({0,0,-10});
		GetMesh()->SetRelativeRotation({0,-90,0});
		GetMesh()->SetRelativeScale3D({2,2,2});
	}
	if(CameraComponent)
	{ 
		CameraComponent->SetFieldOfView(AimScaleNormalValue);
		CameraComponent->SetRelativeScale3D({0.5,0.5,0.5});
	}
	if(SpringArmComponent)
	{ 
		SpringArmComponent->TargetArmLength=80.0;
		SpringArmComponent->TargetOffset={0,0,30};
	}
	//设置运动属性
	if(UCharacterMovementComponent* CharacterMovementComponent=GetCharacterMovement())
	{
		CharacterMovementComponent->MaxWalkSpeed=WalkSpeed; 
	}
}


void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABaseCharacter,bStiffness);
	DOREPLIFETIME(ABaseCharacter,bAiming);
	DOREPLIFETIME(ABaseCharacter,bCrouch);
	DOREPLIFETIME(ABaseCharacter,bRunning);
	DOREPLIFETIME(ABaseCharacter,bIsFiring); 
	DOREPLIFETIME(ABaseCharacter,CameraComponent); 
	DOREPLIFETIME(ABaseCharacter,WeaponComponent); 
	DOREPLIFETIME(ABaseCharacter,HealthComponent); 
	DOREPLIFETIME(ABaseCharacter,PlayerStatComponent); 
	
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this,&ABaseCharacter::OnDeath);
	} 
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//绑定输入到角色控制
	if(const APlayerController* PC = CastChecked<APlayerController>(GetController()))
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
			EnhancedInputComponent->BindAction(RunAction,ETriggerEvent::Started,this,&ABaseCharacter::Action_Running);
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
			EnhancedInputComponent->BindAction(FireAction,ETriggerEvent::Triggered,this,&ABaseCharacter::Action_OnFire);
			EnhancedInputComponent->BindAction(FireAction,ETriggerEvent::Completed,this,&ABaseCharacter::Action_OnEndFire);
		} 
		if(NextWeaponAction) 
		{ 
			EnhancedInputComponent->BindAction(NextWeaponAction,ETriggerEvent::Started,WeaponComponent.Get(),&UWeaponComponent::NextWeapon);
		} 
		if(LastWeaponAction) 
		{ 
			EnhancedInputComponent->BindAction(LastWeaponAction,ETriggerEvent::Started,WeaponComponent.Get(),&UWeaponComponent::LastWeapon);
		}
	}
}

bool ABaseCharacter::IsDeath() const
{
	if(!HealthComponent)return false;
	return HealthComponent->IsDeath();
}

void ABaseCharacter::AddExperience(int Amount)
{
	ExperienceValue+=Amount;
	while (ExperienceValue>=GetMaxExperience())
	{
		Level++;
		UpgradeNum++;
		ExperienceValue-=GetMaxExperience();
	}
}

void ABaseCharacter::OnUpgrade()
{
	UpgradeNum--;
}

void ABaseCharacter::AddMaxHealth(float Amount) const
{
	HealthComponent->AddMaxHealth(Amount);
}

void ABaseCharacter::AddHealValue(float Amount) const
{
	HealthComponent->AddHealValue(Amount);
}

void ABaseCharacter::AddRunningSpeed(float Amount) 
{
	RunSpeed+=Amount;
}

void ABaseCharacter::AddJumpNum()
{
	JumpMaxCount+=1;
}

int ABaseCharacter::GetMaxExperience() const
{
	return 100+Level*50;
}

void ABaseCharacter::UpdateSpeed_Implementation() const
{
	// if(GetLocalRole()==ROLE_Authority)GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black,L"服务器更改速度");
	// if(GetLocalRole()==ROLE_AutonomousProxy)GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black,L"本地客户端更改速度");
	// if(GetLocalRole()==ROLE_SimulatedProxy)GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black,L"模拟客户端更改速度");
	// GEngine->AddOnScreenDebugMessage(-1,1,FColor::Blue,FString::Printf(TEXT("是否奔跑:%hhd"),bRunning));
	if(IsCrouch())	GetCharacterMovement()->MaxWalkSpeed=CrouchSpeed;
	else if(IsAiming()) GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
	else if(IsRunning())  GetCharacterMovement()->MaxWalkSpeed=RunSpeed;
	else GetCharacterMovement()->MaxWalkSpeed=WalkSpeed;
	
}
 

void ABaseCharacter::Action_MoveForward(const FInputActionValue& Value)
{
	if(!Can_Move())return; 
	UpdateSpeed();
	UE_LOG(LogBaseCharacter,Display,TEXT("前后移动"));
	AddMovementInput(CameraComponent->GetForwardVector(),Value.Get<float>());
}


void ABaseCharacter::Action_MoveRight(const FInputActionValue& Value)
{
	if(!Can_Move())return;
	UpdateSpeed();
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

void ABaseCharacter::Action_Running_Implementation()
{
	if(!Can_Run())return;   
	check(GetCharacterMovement());
	bRunning=true; 
} 
void ABaseCharacter::Action_EndRun_Implementation()
{
	UE_LOG(LogBaseCharacter,Display,TEXT("结束奔跑")); 
	check(GetCharacterMovement());  
	bRunning=false;
} 
void ABaseCharacter::Action_Crouch_Implementation()
{ 
	if(IsStiff() || IsRunning())return;
	UE_LOG(LogBaseCharacter,Display,TEXT("蹲下")); 
	bCrouch=true;
	check(GetCharacterMovement()); 
} 
void ABaseCharacter::Action_EndCrouch_Implementation()
{

	UE_LOG(LogBaseCharacter,Display,TEXT("起身")); 
	bCrouch=false; 
	check(GetCharacterMovement()); 
}
void ABaseCharacter::Action_StartAim_Implementation()
{
	check(CameraComponent);
	check(GetWorld());
	GetWorldTimerManager().SetTimer(AimScaleTimeHandle, this, &ABaseCharacter::AimScaleAmplifier,AimScaleRate, true);
	GetController()->GetPawn()->bUseControllerRotationYaw=true;
	bAiming=true;
}
void ABaseCharacter::Action_EndAim_Implementation()
{
	check(CameraComponent);
	check(GetWorld());  
	GetWorldTimerManager().SetTimer(AimScaleTimeHandle,this,&ABaseCharacter::AimScaleReduce,AimScaleRate,true);
	GetController()->GetPawn()->bUseControllerRotationYaw=false;
	bAiming=false;
}
void ABaseCharacter::AimScaleAmplifier()
{
	//每次放大多少
	const float ScaleValue=(AimScaleNormalValue-AimScaleTargetValue)/(AimScaleTime/AimScaleRate);
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
	const float ScaleValue=(AimScaleNormalValue-AimScaleTargetValue)/(AimScaleTime/AimScaleRate);
	CameraComponent->SetFieldOfView(CameraComponent->FieldOfView+ScaleValue);
	if(CameraComponent->FieldOfView>=AimScaleNormalValue)
	{
		UE_LOG(LogBaseCharacter,Display,TEXT("视角缩小完成"));
		GetWorldTimerManager().ClearTimer(AimScaleTimeHandle);
	}
}

FHitResult ABaseCharacter::GetAimResult() const
{
	const AController* OwnerController=GetController();
	if(!OwnerController)return {};

	FVector ViewLocation;
	FRotator ViewRotation;
	OwnerController->GetPlayerViewPoint(ViewLocation,ViewRotation); 
	FVector EndPoint=ViewLocation+ViewRotation.Vector()*10000;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult,ViewLocation,EndPoint,ECC_Visibility,CollisionQueryParams);
	return HitResult;
}


void ABaseCharacter::Action_OnFire_Implementation()
{ 
	if(!WeaponComponent)return;
	WeaponComponent->Fire();
	bIsFiring=true;
} 

void ABaseCharacter::Action_OnEndFire_Implementation()
{
	bIsFiring=false;
}
 
void ABaseCharacter::OnDeath(AController* InstigatedBy) 
{
	GEngine->AddOnScreenDebugMessage(01,1,FColor::Blue,L"角色死亡");
	//停止控制
	GetCharacterMovement()->DisableMovement();  
	if (Controller)
	{
		//转移旁观者
		Controller->ChangeState(NAME_Spectating); 
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
	//启动物理模拟
	if(GetMesh())
	{ 
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetAllBodiesPhysicsBlendWeight(1);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);		
	}
	
	if(WeaponComponent && WeaponComponent->GetCurrentWeapon())
	{
		WeaponComponent->GetCurrentWeapon()->SetLifeSpan(5);
	}
	SetLifeSpan(5);
	if(InstigatedBy){
		ABaseCharacter* Character=Cast<ABaseCharacter>(InstigatedBy->GetCharacter());
		Character->AddExperience(Experience);

	}
}
 
