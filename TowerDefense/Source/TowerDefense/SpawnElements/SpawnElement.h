// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "SpawnElement.generated.h"

class ADefenderCharacter;
class UInventoryComponent;
UCLASS()
class TOWERDEFENSE_API ASpawnElement : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollider;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory);
};
