// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PGhost.h"
#include "PPowerPellet.generated.h"

class UStaticMeshComponent; 
struct FTimerHandle; 

UCLASS()
class PACMAN_API APPowerPellet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APPowerPellet();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
public:	

	void BeginPlay();

	UFUNCTION()
	void OnPelletHit(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void EndPowerPelletEffect();

	UFUNCTION()
	void StartPowerPelletEffect();

	UPROPERTY()
	FTimerHandle PowerPelletTimerHandle;
};
