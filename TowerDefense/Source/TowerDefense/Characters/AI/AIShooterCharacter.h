// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefense/Characters/BaseCharacter.h"
#include "AIShooterCharacter.generated.h"

class UPawnSensingComponent;
class UBehaviorTree;
class UWidgetComponent;
class AAIControllerShooterCharacter;
UCLASS()
class TOWERDEFENSE_API AAIShooterCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAIShooterCharacter();

	virtual void BeginPlay() override;

	/*A Pawn Sensing Component, responsible for sensing other Pawns*/
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensingComp;

	/*A Behavior Tree reference*/
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = HealthBar)
	UWidgetComponent* HealthWidgetComp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Drop)
	TArray<TSubclassOf<ACraftingMaterial>> ClassDropMaterial;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = GamePlay)
	bool bInFinallyLocation;

	UFUNCTION(BlueprintCallable)
	void Die() override;

	UFUNCTION(BlueprintCallable)
	void OnSeePawn(APawn* Pawn);

private:
	UFUNCTION()
	void CantSeePlayer(AAIControllerShooterCharacter* ControllerShooterCharacter);

	UFUNCTION()
	void SpawnCraftingMaterial();

	bool bCanSeePlayer;
	APawn* VisiblePlayer;
};
