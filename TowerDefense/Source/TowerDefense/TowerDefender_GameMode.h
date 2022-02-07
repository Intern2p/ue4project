// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TowerDefender_GameMode.generated.h"

class ASpawnerAIShooterCharacters;
class AAIShooterCharacter;
class ATargetLocation;
class AFPSHUD;

/* Struct to avoid the problem of nested collections */
USTRUCT(BlueprintType)
struct FKeyWavesMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GameSettings)
		TArray<TSubclassOf<AAIShooterCharacter>> Mobs;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GameSettings)
		float FrequencySpawn;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GameSettings)
		float BreakTimeBefore;
};

UCLASS()
class TOWERDEFENSE_API ATowerDefender_GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ATowerDefender_GameMode();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GameSettings)
	TArray<FKeyWavesMap> Waves;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = GameSettings)
	int IndexCurrentWave;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = GameSettings)
	int IndexCurrentMob;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<ASpawnerAIShooterCharacters*> Spawners;

	AFPSHUD* PlayerHUD;

	FTimerHandle TimerHandleWaveBreak;
	FTimerHandle TimerHandleSpawnMob;

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void StartWave();

	UFUNCTION()
	void SpawnMob(TSubclassOf<AAIShooterCharacter> ClassChar);

	UFUNCTION()
	void ShowWidgetWaveBegin();

};
