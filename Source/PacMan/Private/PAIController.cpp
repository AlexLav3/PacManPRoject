// Fill out your copyright notice in the Description page of Project Settings.

#include "PAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"

void APAIController::BeginPlay()
{
    Super::BeginPlay();

    RunBehaviorTree(BehaviourTree);
    bScatterMode = false;
    ToggleScatterChaseMode();
}

void APAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    Update();
}

void APAIController::UpdatePinkGhostTargetLocation()
{
    APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    FVector PlayerLocation = MyPawn->GetActorLocation();
    float OffsetDistance = 80.0f;

    // Calculate the target location to the left of the player
    FVector PinkGhostTargetLocation = PlayerLocation - MyPawn->GetActorRightVector() * OffsetDistance;

    // Set the Pink Ghost's target location
    GetBlackboardComponent()->SetValueAsVector("PinkGhostTarget", PinkGhostTargetLocation);
}

void APAIController::UpdateInkyTargetLocation()
{
    if (!bScatterMode)
    {
        APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);

        float OffsetDistance = 80.0f;

        FVector PlayerLocation = MyPawn->GetActorLocation();
        // Calculate the target location to the left of the player
        FVector PinkGhostTargetLocation = PlayerLocation - MyPawn->GetActorRightVector() * OffsetDistance;

        // Calculate Inky's target location based on Pinky's target and the player's location
        FVector InkyTarget = PlayerLocation * (PlayerLocation - PinkGhostTargetLocation);

        // Set Inky's target location in the blackboard
        GetBlackboardComponent()->SetValueAsVector("InkyTarget", InkyTarget);
    }
}

void APAIController::UpdataRedTargetLocation()
{
    if (!bScatterMode)
    {
        APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);

        // GetBlackboardComponent() ->SetValueAsVector("MoveToTarget", MyPawn->GetActorLocation());

        GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
    }
}

void APAIController::UpdateOrangeGhostTargetLocation()
{
    if (!bScatterMode)
    {
        APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);

        FVector PlayerLocation = MyPawn->GetActorLocation();
        GetBlackboardComponent()->SetValueAsVector("OrangeTargetActor", PlayerLocation);

        // Calculate the distance between Orange Ghost and Pac-Man
        FVector OrangeGhostLocation = GetPawn()->GetActorLocation();
        float DistanceToPlayer = FVector::Distance(OrangeGhostLocation, PlayerLocation);

        // Define the threshold distance for switching to scatter mode
        float ScatterThreshold = 80.0f; // Adjust as needed

        // Check if the Orange Ghost is within the scatter threshold
        if (DistanceToPlayer <= ScatterThreshold)
        {
            // Set the scatter target location
            FVector OrangeScatterTargetLocation = FVector(-2590.0f, -2770.0f, 88.0f);
            GetBlackboardComponent()->SetValueAsVector("OrangeScatterTarget", OrangeScatterTargetLocation);
        }
    }
}

void APAIController::ToggleScatterChaseMode()
{
    // Toggle between Scatter and Chase modes
    bScatterMode = !bScatterMode;

    // Set the next mode duration
    float NextModeDuration = bScatterMode ? ScatterDuration : ChaseDuration;

    // Reset the timer for the next mode
    GetWorldTimerManager().SetTimer(ScatterChaseTimerHandle, this, &APAIController::ToggleScatterChaseMode, NextModeDuration, false);
}

void APAIController::Update()
{
    if (bScatterMode)
    {
        FVector RedTargetLocationS = FVector(2620.0, 2810.0, 88);
        GetBlackboardComponent()->SetValueAsVector("RedScatterTarget", RedTargetLocationS);

        FVector PinkTargetLocationS = FVector(2620.0, -2810.0, 88);
        GetBlackboardComponent()->SetValueAsVector("PinkScatterTarget", PinkTargetLocationS);

        FVector BlueTargetLocationS = FVector(-2590.0, 2770.0, 88);
        GetBlackboardComponent()->SetValueAsVector("BlueScatterTarget", BlueTargetLocationS);

        FVector OrangeTargetLocationS = FVector(-2590.0, -2770.0, 88);
        GetBlackboardComponent()->SetValueAsVector("OrangeScatterTarget", OrangeTargetLocationS);
    }
    else
    {
        UpdataRedTargetLocation();
        UpdatePinkGhostTargetLocation();
        UpdateInkyTargetLocation();
        UpdateOrangeGhostTargetLocation();
    }
}