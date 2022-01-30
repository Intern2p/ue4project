// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerShooterCharacter.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
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
	class UBehaviorTreeComponent* BehaviorTreeComp;

	/*UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;*/

	UPROPERTY(EditDefaultsOnly, Category = AI)
	class UBlackboardComponent* BlackboardComp;

	/*This property is used to find a certain key for our blackboard.
	We will create the blackboard later in this tutorial*/
	UPROPERTY(EditDefaultsOnly)
	FName TargetKey = "Target";

	/*Sets the new sensed target value inside our Blackboard values*/
	//void SetSensedTarget(APawn* NewTarget);
	void SetTargetLocation(FVector NewTarget);
	void SetPlayerSighted(bool isPlayerCanSee);

	//UFUNCTION(BlueprintImplementableEvent)
	//void TryToFire(AAIControllerShooterCharacter* OwnerController, APawn* ControlledPawn);

protected:

private:
	FVector FinallyLocation;
	//class UBlackboardComponent* BlackboardComp;
};
