// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Kismet/GameplayStatics.h>
#include "PGhost.h"
#include "PAIController.generated.h"

/**
 * 
 */

class UBehaviorTree;
struct FTimerHandle; 

UCLASS()
class PACMAN_API APAIController : public AAIController
{
	GENERATED_BODY()
	

protected: 

	UPROPERTY (EditDefaultsOnly, Category="AI")
	UBehaviorTree* BehaviourTree; 


	virtual void BeginPlay() override;

	void Tick(float DeltaSeconds);

	void UpdatePinkGhostTargetLocation();

	void UpdateBlueTargetLocation(const FVector& PinkGhostTargetLocation);

	void UpdataRedTargetLocation();

	void UpdateOrangeGhostTargetLocation();

    void ToggleScatterChaseMode();

	void Update();

	void ResetScatterMode();

	bool bScatterMode; 

	UPROPERTY()
	FTimerHandle ScatterChaseTimerHandle;

	//Declare Scatter and Chase durations
	//float ScatterDuration = 10.0f;
	//float ChaseDuration = 10.0f;

	APawn* MyPawn; // Declare MyPawn here

	FVector PlayerLocation; // Declare PlayerLocation here

};
