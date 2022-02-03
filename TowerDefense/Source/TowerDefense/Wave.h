// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AAIShooterCharacter;
//UCLASS()
class TOWERDEFENSE_API Wave
{
public:
	Wave();
	~Wave();

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GameSettings)
	TArray<TSubclassOf<AAIShooterCharacter>> Mobs;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GameSettings)
	float FrequencySpawn;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GameSettings)
	float BreakTimeBefore;
};
