// Fill out your copyright notice in the Description page of Project Settings.

#include "PGhost.h"
#include "PAIController.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APGhost::APGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APGhost::OnGhostHit);
}

// Called when the game starts or when spawned
void APGhost::BeginPlay()
{
	Super::BeginPlay();
   
}

// Called every frame
void APGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APGhost::OnGhostHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    APPacMan* PacMan = Cast<APPacMan>(OtherActor);
    if (PacMan)
    {
        if (PacMan->bHasConsumedPowerPellet)
        {
            TeleportToLocation(); // Destroy the ghost if Pac-Man has consumed a power pellet
            PacMan->HighScore += 100; 
        }
        else 
        {
            UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
        }
    }

}

void APGhost::TeleportToLocation()
{
    FVector TeleportLocation = FVector(-10.0f, 210.0f, 88.0f);
    SetActorLocation(TeleportLocation);

}