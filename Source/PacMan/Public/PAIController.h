// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PAIController.generated.h"

/**
 * 
 */

class UBehaviorTree;

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

	void UpdateInkyTargetLocation();

	void UpdataRedTargetLocation();

	void UpdateOrangeGhostTargetLocation();

	void ToggleScatterChaseMode();
	void Update(); 
	bool bScatterMode; 

	FTimerHandle ScatterChaseTimerHandle;

	// Declare Scatter and Chase durations
	float ScatterDuration = 10.0f;
	float ChaseDuration = 7.0f;
    
};
