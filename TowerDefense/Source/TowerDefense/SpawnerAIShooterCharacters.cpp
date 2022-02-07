// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerAIShooterCharacters.h"
#include "TowerDefense/Characters/AI/AIShooterCharacter.h"
#include "TowerDefense/Characters/AI/AIControllerShooterCharacter.h"
#include "TargetLocation.h"
#include "Kismet/GameplayStatics.h"

void ASpawnerAIShooterCharacters::BeginPlay()
{
	/*Get Target Location*/
	TArray<AActor*> FoundTarget;

	TSubclassOf<ATargetLocation> classNameLocation = ATargetLocation::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classNameLocation, FoundTarget);
	for (AActor* TActor : FoundTarget)
	{
		FinallyLocation = Cast<ATargetLocation>(TActor);
	}
}

void ASpawnerAIShooterCharacters::SpawnMob(TSubclassOf<AAIShooterCharacter> ClassChar)
{
	AAIShooterCharacter* Char = GetWorld()->SpawnActor<AAIShooterCharacter>(ClassChar, GetActorLocation(), GetActorRotation());
	if (FinallyLocation != nullptr && Char)
	{
		AAIControllerShooterCharacter* AIController = Cast<AAIControllerShooterCharacter>(Char->GetController());
		AIController->FinallyLocation = FinallyLocation;
		AIController->SetTargetLocation(FinallyLocation->GetActorLocation());
	}
}