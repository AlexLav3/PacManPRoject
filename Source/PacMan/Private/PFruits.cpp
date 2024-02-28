// Fill out your copyright notice in the Description page of Project Settings.
#include "PFruits.h"
#include "Components/PrimitiveComponent.h"
#include "PPacMan.h"


// Sets default values
APFruits::APFruits()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BaseMesh->SetCollisionResponseToAllChannels(ECR_Block);
	BaseMesh->OnComponentHit.AddDynamic(this, &APFruits::OnFruitHit);

}

// Called when the game starts or when spawned
void APFruits::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APFruits::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//oid APFruits::GetsEaten(bool bIsEaten)
//{
//	if (bIsEaten) {
	//	bHasBeenEaten = true;

	//	if (APPacMan* PacMan = Cast<APPacMan>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	//	{
//PacMan->HighScore++;
	//	}
	//	Destroy();
	//}
//}

void APFruits::OnFruitHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherComponent)
	{
		// Check if the other actor is the player character
		APPacMan* PacMan = Cast<APPacMan>(OtherActor);
		if (PacMan)
		{
			// Increment the high score of the player character
			PacMan->HighScore++;

			// Set the fruit as eaten and destroy it
			bHasBeenEaten = true;
			Destroy();
		}
	}
}
