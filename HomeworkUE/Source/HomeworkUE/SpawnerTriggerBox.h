// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SpawnerTriggerBox.generated.h"

class APlacableActor;

UCLASS()
class HOMEWORKUE_API ASpawnerTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
public:
	// Sets default values for this properties
	ASpawnerTriggerBox();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// constructor sets default values for this actor's properties

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Spawn")
	TSubclassOf<APlacableActor> ActorToSpawn;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Spawn")
	int MaxCountActors;

	UFUNCTION(BlueprintCallable)
	void PlacableActorSpawn();

	UFUNCTION(BlueprintCallable)
	void CalculateValues();

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	void PostInitProperties();

};
