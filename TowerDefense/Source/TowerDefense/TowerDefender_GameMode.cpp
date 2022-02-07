// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefender_GameMode.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "TargetLocation.h"
#include "TowerDefense/Characters/AI/AIShooterCharacter.h"
#include "TowerDefense/Characters/AI/AIControllerShooterCharacter.h"
#include "SpawnerAIShooterCharacters.h"
#include "Kismet/GameplayStatics.h"
#include "FPSHUD.h"

ATowerDefender_GameMode::ATowerDefender_GameMode()
{
	static ConstructorHelpers::FClassFinder<ADefenderCharacter> DefenderCharacterBPClass(TEXT("/Game/MyBPClasses/BP_DefenderCharacter"));
	if (DefenderCharacterBPClass.Class != NULL)
	{
		DefaultPawnClass = DefenderCharacterBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AFPSHUD> FPSHUDBPClass(TEXT("/Game/MyBPClasses/BP_FPSHUD"));
	if (FPSHUDBPClass.Class != NULL)
	{
		HUDClass = FPSHUDBPClass.Class;
	}

	IndexCurrentWave = 0;
	IndexCurrentMob = 0;
}

void ATowerDefender_GameMode::BeginPlay()
{
	Super::BeginPlay();

	/* Get Spawners */
	TArray<AActor*> FoundTarget;
	TSubclassOf<ASpawnerAIShooterCharacters> classNameSpawner = ASpawnerAIShooterCharacters::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classNameSpawner, FoundTarget);
	for (AActor* TActor : FoundTarget)
	{
		ASpawnerAIShooterCharacters* Spawner = Cast<ASpawnerAIShooterCharacters>(TActor);
		if (Spawner != nullptr)
		{
			Spawners.Add(Spawner);
		}
	}

	/*Get Target Location*/
	TSubclassOf<ATargetLocation> classNameLocation = ATargetLocation::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classNameLocation, FoundTarget);
	for (AActor* TActor : FoundTarget)
	{
		FinallyLocation = Cast<ATargetLocation>(TActor);	
	}

	PlayerHUD = Cast<AFPSHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	/* Start Waves */
	if (Waves.Num() > 0)
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDel;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATowerDefender_GameMode::StartGame, Waves[IndexCurrentWave].BreakTimeBefore, false);
	}
}

void ATowerDefender_GameMode::StartGame()
{
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Wave num %d"), IndexCurrentWave));
	IndexCurrentMob = 0;

	if (IndexCurrentWave >= Waves.Num() - 1)
	{
		return;
	}

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATowerDefender_GameMode::StartWave, Waves[IndexCurrentWave].BreakTimeBefore, false);
}

/* recursion */
void ATowerDefender_GameMode::StartWave()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Purple, FString::Printf(TEXT("Mob num %d"), IndexCurrentMob));
	if (IndexCurrentMob == 0)
		ShowWidgetWaveBegin();

	if (IndexCurrentMob >= Waves[IndexCurrentWave].Mobs.Num() - 1)
	{
		IndexCurrentWave++;
		StartGame();
		return;
	}

	TSubclassOf<AAIShooterCharacter> Mob = Waves[IndexCurrentWave].Mobs[IndexCurrentMob]; 
	IndexCurrentMob++;

	if (Mob)
		SpawnMob(Mob);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATowerDefender_GameMode::StartWave, Waves[IndexCurrentWave].FrequencySpawn, false);
}

void ATowerDefender_GameMode::SpawnMob(TSubclassOf<AAIShooterCharacter> ClassChar)
{
	if (Spawners.Num() > 0)
	{
		int StartRange = 0;
		int EndRange = Spawners.Num() - 1;

		int index = FMath::RandRange(StartRange, EndRange);
		AAIShooterCharacter* Char = GetWorld()->SpawnActor<AAIShooterCharacter>(ClassChar, Spawners[index]->GetActorLocation(), Spawners[index]->GetActorRotation());
		if (FinallyLocation != nullptr)
		{
			AAIControllerShooterCharacter* AIController = Cast<AAIControllerShooterCharacter>(Char->GetController());
			AIController->FinallyLocation = FinallyLocation;
			AIController->SetTargetLocation(FinallyLocation->GetActorLocation());
		}
	}
}

void ATowerDefender_GameMode::ShowWidgetWaveBegin()
{
	if (PlayerHUD)
		PlayerHUD->ShowStageWaveWidget();
}

