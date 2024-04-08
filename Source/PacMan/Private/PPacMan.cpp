// Fill out your copyright notice in the Description page of Project Settings.

#include "PPacMan.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "C:/Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputTriggers.h"
#include "EnhancedInputComponent.h"
#include "PFruits.h"
#include "EnhancedInputSubsystems.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APPacMan::APPacMan()
{
	// Set this character to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	// Set up character movement
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Create camera component
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	
	HighScore = 0;
	bHasConsumedPowerPellet = false;
	Won = false;
}

// Called when the game starts or when spawned
void APPacMan::BeginPlay()
{
	Super::BeginPlay();

	CameraComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
    CameraComp->SetWorldLocation(FVector(30.0f, 0.0f, 6000.0f));
	CameraComp->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f)); // Set the rotation to look straight down

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (IsValid(PlayerController) && IsValid(CameraComp))
		{
			PlayerController->SetViewTargetWithBlend(this, 0.0f);
		}
	  	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void APPacMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APPacMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APPacMan::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APPacMan::Look);

	}

}

void APPacMan::Move(const FInputActionValue& Value)
{

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Forward vector in world space
		const FVector ForwardDirection = GetActorForwardVector();

		// Right vector in world space 
		const FVector RightDirection = GetActorRightVector();

		// Add movement in the direction of the input
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

}

void APPacMan::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		//  yaw and pitch input 
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
 