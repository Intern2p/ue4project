// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerShooterCharacter.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
class ATargetLocation;
UCLASS()
class TOWERDEFENSE_API AAIControllerShooterCharacter : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIControllerShooterCharacter(/*FObjectInitializer const& object_initializer = FObjectInitializer::Get()*/);
	void BeginPlay() override;
	void OnPossess(APawn* const pawn) override;
	//class UBlackboardComponent* get_blackboard() const;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	ATargetLocation* FinallyLocation;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly)
	FName TargetKey = "Target";

	/*Sets the new sensed target value inside our Blackboard values*/
	void SetTargetLocation(FVector NewTarget);
	void SetPlayerSighted(bool isPlayerCanSee);


};
