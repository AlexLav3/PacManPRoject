// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <PPacMan.h>
#include "Kismet/KismetSystemLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "PGhost.generated.h"


UCLASS()
class PACMAN_API APGhost : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnGhostHit(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void TeleportToLocation();

};
