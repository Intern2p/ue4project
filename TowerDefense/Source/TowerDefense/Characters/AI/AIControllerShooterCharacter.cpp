// Fill out your copyright notice in the Description page of Project Settings.

#include "AIControllerShooterCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TowerDefense/TargetLocation.h"
#include "UObject/ConstructorHelpers.h"
#include "AIShooterCharacter.h"
#include "Kismet/GameplayStatics.h"

AAIControllerShooterCharacter::AAIControllerShooterCharacter(/*FObjectInitializer const& object_initializer*/)
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AAIControllerShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AAIControllerShooterCharacter::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	AAIShooterCharacter* Char = Cast<AAIShooterCharacter>(pawn);

	if (Char && Char->BehaviorTree->BlackboardAsset)
	{
		//Initialize the blackboard values
		BlackboardComp->InitializeBlackboard(*Char->BehaviorTree->BlackboardAsset);

		//Start the tree
		BehaviorTreeComp->StartTree(*Char->BehaviorTree);
	}
}

void AAIControllerShooterCharacter::SetTargetLocation(FVector NewTarget)
{
	if (BlackboardComp) BlackboardComp->SetValueAsVector("Location", NewTarget);
}

void AAIControllerShooterCharacter::SetPlayerSighted(bool isPlayerCanSee)
{
	if (BlackboardComp) BlackboardComp->SetValueAsBool("PlayerSighted", isPlayerCanSee);
}
