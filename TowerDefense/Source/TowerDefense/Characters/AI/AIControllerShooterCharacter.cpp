// Fill out your copyright notice in the Description page of Project Settings.

#include "AIControllerShooterCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "AIShooterCharacter.h"
#include "TowerDefense/TargetLocation.h"
#include "Kismet/GameplayStatics.h"

AAIControllerShooterCharacter::AAIControllerShooterCharacter(/*FObjectInitializer const& object_initializer*/)
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AAIControllerShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundTarget;
	TSubclassOf<ATargetLocation> className = ATargetLocation::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), className, FoundTarget);
	for (AActor* TActor : FoundTarget)
	{
		FinallyLocation = Cast<ATargetLocation>(TActor);
		if (FinallyLocation != nullptr)
		{
			SetTargetLocation(FinallyLocation->GetActorLocation());
		}
	}
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
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Location %d %d %d"), NewTarget.X, NewTarget.Y, NewTarget.Z));
}

void AAIControllerShooterCharacter::SetPlayerSighted(bool isPlayerCanSee)
{
	if (BlackboardComp) BlackboardComp->SetValueAsBool("PlayerSighted", isPlayerCanSee);
}
