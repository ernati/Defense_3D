// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AttackTower.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"
#include "BagComponent.h"
#include "GameFramework/PlayerController.h"
#include "AttackTowerProjectile.h"
#include "TimerManager.h"


//////////////////////////////////////////////////////////////////////////
// AFPSCharacter

AFPSCharacter::AFPSCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -84.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f) );

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform);
	FollowCamera->SetRelativeLocation(FVector(0.0f, 28.0f, 163.0f));
	FollowCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

	FollowCamera->bUsePawnControlRotation = true; // Camera does not rotate relative to arm

	bagcomponent = CreateDefaultSubobject<UBagComponent>(TEXT("bagcomponent"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AFPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			Subsystem->AddMappingContext(IC_Build, 1);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);

		//Build
		EnhancedInputComponent->BindAction(IA_Build, ETriggerEvent::Started, this, &AFPSCharacter::Build);

		EnhancedInputComponent->BindAction(IA_Shoot, ETriggerEvent::Started, this, &AFPSCharacter::ShootStart);
		EnhancedInputComponent->BindAction(IA_Shoot, ETriggerEvent::Completed, this, &AFPSCharacter::ShootStop);
	}

}

void AFPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

	}
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSCharacter::Build(const FInputActionValue& Value)
{
	if (ReturnPoint() >= TowerCost) {
		if (Controller != nullptr)
		{
			// 현재 위치에 AttackTower를 생성하기
			if (attackTower)
			{
				UWorld* World = GetWorld();
				if (World)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;

					//const FVector SpawnLocation = scenecomp->GetComponentLocation();
					const FVector SpawnLocation = GetActorLocation();
					//const FRotator Rotation = GetActorForwardVector().Rotation();

					FRotator Rotation = GetActorForwardVector().Rotation();

					AAttackTower* attacktowers = World->SpawnActor<AAttackTower>(attackTower, SpawnLocation, Rotation, SpawnParams);

					bagcomponent->UsePoint(TowerCost);
				}
			}
		}
	}

	else {
		if (Controller)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You Can't Buy Tower!"));
		}
	}

}

void AFPSCharacter::ShootStart(const FInputActionValue& Value)
{
	//총쏘기를 시작한다
	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AFPSCharacter::SpawnProjectile, ShootingDelay, true, 0.0f);
}

void AFPSCharacter::ShootStop(const FInputActionValue& Value)
{
	//총 쏘기를 멈춘다.
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
}

void AFPSCharacter::SpawnProjectile()
{
	if (attackTowerProjectile)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			//const FVector SpawnLocation = scenecomp->GetComponentLocation();
			//const FVector SpawnLocation = GetActorLocation();
			const FVector SpawnLocation = FollowCamera->GetComponentLocation();
			//const FRotator Rotation = GetActorForwardVector().Rotation();

			//FVector End = CameraBoom->GetComponentLocation();
			//FVector End = SpawnLocation;

			//FVector Start = FollowCamera->GetComponentLocation();

			//FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
			auto b = FollowCamera->GetComponentRotation();

			//AAttackTowerProjectile* projectiles = World->SpawnActor<AAttackTowerProjectile>(attackTowerProjectile, SpawnLocation, Rotation, SpawnParams);
			AAttackTowerProjectile* projectiles = World->SpawnActor<AAttackTowerProjectile>(attackTowerProjectile, SpawnLocation, b, SpawnParams);

		}
	}
}


int32 AFPSCharacter::ReturnPoint()
{
	return bagcomponent->ReturnPoint();
}

void AFPSCharacter::GetPoint()
{
	return bagcomponent->GetPoint();
}

void AFPSCharacter::GetPoints(int32 Amount)
{
	return bagcomponent->GetPoints(Amount);
}



