// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefense/Characters/BaseCharacter.h"
#include "AIShooterCharacter.generated.h"

class UPawnSensingComponent;
class UBehaviorTree;
class UWidgetComponent;
UCLASS()
class TOWERDEFENSE_API AAIShooterCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAIShooterCharacter();
	void Tick(float DeltaTime);

	virtual void BeginPlay() override;

	/*A Pawn Sensing Component, responsible for sensing other Pawns*/
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensingComp;

	/*A Behavior Tree reference*/
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = HealthBar)
	UWidgetComponent* HealthWidgetComp;

	/*Hearing function - will be executed when we hear a Pawn*/
//	UFUNCTION()
	//void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);
	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

private:
	bool bCanSeePlayer;
	APawn* VisiblePlayer;
};
