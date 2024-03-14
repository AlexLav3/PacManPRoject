// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PFruits.generated.h"

class UStaticMeshComponent; 

UCLASS()
class PACMAN_API APFruits : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APFruits();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	bool bHasBeenEaten=false;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void GetsEaten(bool bIsEaten); 

	UFUNCTION()
	void OnFruitHit(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
    int FruitsEaten; 
};
