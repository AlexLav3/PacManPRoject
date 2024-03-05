// Fill out your copyright notice in the Description page of Project Settings.


#include "PPowerPellet.h"

// Sets default values
APPowerPellet::APPowerPellet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    RootComponent = BaseMesh;
    BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BaseMesh->SetCollisionResponseToAllChannels(ECR_Block);
    BaseMesh->OnComponentHit.AddDynamic(this, &APPowerPellet::OnPelletHit);
}


void APPowerPellet::BeginPlay()
{
    Super::BeginPlay();
}

void APPowerPellet::OnPelletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    APPacMan* PacMan = Cast<APPacMan>(OtherActor);
    if (PacMan)
    {
        PacMan->bHasConsumedPowerPellet = true;
        StartPowerPelletEffect();
    }
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

}
void APPowerPellet::EndPowerPelletEffect()
{
 APPacMan* PacMan = Cast<APPacMan>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

     PacMan->bHasConsumedPowerPellet = false;
}

void APPowerPellet::StartPowerPelletEffect()
{
    GetWorldTimerManager().SetTimer(PowerPelletTimerHandle, this, &APPowerPellet::EndPowerPelletEffect, 5.0f, false);
}
