// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "SpawnerAIShooterCharacters.generated.h"

class ATargetLocation;
class AAIShooterCharacter;
UCLASS()
class TOWERDEFENSE_API ASpawnerAIShooterCharacters : public ATriggerBox
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void SpawnMob(TSubclassOf<AAIShooterCharacter> ClassChar);

private:
	ATargetLocation* FinallyLocation;
};
