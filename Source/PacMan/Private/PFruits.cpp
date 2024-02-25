// Fill out your copyright notice in the Description page of Project Settings.


#include "PFruits.h"

// Sets default values
APFruits::APFruits()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;
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

void APFruits::GetsEaten(bool* bIsEaten)
{
	if (bIsEaten && *bIsEaten) {
		HighScore++;
		Destroy();
	}
}

