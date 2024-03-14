// Fill out your copyright notice in the Description page of Project Settings.

#include "PAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"


void APAIController::BeginPlay()
{
    Super::BeginPlay();
    

    RunBehaviorTree(BehaviourTree);
    bScatterMode = true;
    GetBlackboardComponent()->SetValueAsBool("bScatterMode", bScatterMode);

    ToggleScatterChaseMode(); 
}

void APAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    // Check if MyPawn is valid before accessing its properties
    if (MyPawn) {
        PlayerLocation = MyPawn->GetActorLocation();
    }
    Update();
}

void APAIController::UpdatePinkGhostTargetLocation()
{
    float OffsetDistance = 5.0f;

    // Calculate the target location to the left of the player
    FVector PinkGhostTargetLocation = PlayerLocation - MyPawn->GetActorRightVector() * OffsetDistance;

    // Set the Pink Ghost's target location
    GetBlackboardComponent()->SetValueAsVector("PinkGhostTarget", PinkGhostTargetLocation);
}

void APAIController::UpdateBlueTargetLocation()
{
      FVector PinkGhostTargetLocation = GetBlackboardComponent()->GetValueAsVector("PinkGhostTarget");
       FVector BlueTarget = PlayerLocation + (PinkGhostTargetLocation - PlayerLocation);

        // Set Inky's target location in the blackboard
        GetBlackboardComponent()->SetValueAsVector("BlueTarget", BlueTarget);
    
}

void APAIController::UpdataRedTargetLocation()
{

   GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
}

void APAIController::UpdateOrangeGhostTargetLocation()
{
    
        GetBlackboardComponent()->SetValueAsVector("OrangeTargetActor", PlayerLocation);

        // Calculate the distance between Orange Ghost and Pac-Man
        FVector OrangeGhostLocation = GetPawn()->GetActorLocation();
        float DistanceToPlayer = FVector::Distance(OrangeGhostLocation, PlayerLocation);

        // Define the threshold distance for switching to scatter mode
        float ScatterThreshold = 5.0f; // Adjust as needed

        // Check if the Orange Ghost is within the scatter threshold
        if (DistanceToPlayer == ScatterThreshold)
        {
            GetBlackboardComponent()->SetValueAsVector("OrangeScatterTarget", FVector(-2590.0f, -2770.0f, 88.0f));
        }
    
}


void APAIController::Update()
{
    if (!bScatterMode)
    { 
        UE_LOG(LogTemp, Warning, TEXT("NOT Scattermode "));
        UpdataRedTargetLocation();
        UpdatePinkGhostTargetLocation();
        UpdateBlueTargetLocation();
        UpdateOrangeGhostTargetLocation(); 
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("YES Scattermode "));
       GetBlackboardComponent()->SetValueAsVector("RedScatterTarget", FVector(2620.0, 2810.0, 88));

        GetBlackboardComponent()->SetValueAsVector("PinkScatterTarget",FVector(2620.0, -2810.0, 88));

        GetBlackboardComponent()->SetValueAsVector("BlueScatterTarget",FVector(-2590.0, 2770.0, 88));

       GetBlackboardComponent()->SetValueAsVector("OrangeScatterTarget",FVector(-2590.0, -2770.0, 88));
    }
    
}

 void APAIController::ResetScatterMode()
{
     UE_LOG(LogTemp, Warning, TEXT("ResetScatterMode called"));

     if (!bScatterMode) {
         bScatterMode = true;
         GetBlackboardComponent()->SetValueAsBool("bScatterMode", bScatterMode);
     }
     else {
         bScatterMode = false;
         GetBlackboardComponent()->SetValueAsBool("bScatterMode", bScatterMode);
     }
} 

void APAIController::ToggleScatterChaseMode()
{
    // Reset the timer for the next mode
    GetWorldTimerManager().SetTimer(ScatterChaseTimerHandle, this, &APAIController::ResetScatterMode, 10.0f, true);

}
