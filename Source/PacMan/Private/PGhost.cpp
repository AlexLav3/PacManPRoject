// Fill out your copyright notice in the Description page of Project Settings.


#include "PGhost.h"

// Sets default values
APGhost::APGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
            Destroy(); // Destroy the ghost if Pac-Man has consumed a power pellet
        }
        else
        {
           
            UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
        }
    }

}