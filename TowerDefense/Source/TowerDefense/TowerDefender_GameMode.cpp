// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefender_GameMode.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
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
}
