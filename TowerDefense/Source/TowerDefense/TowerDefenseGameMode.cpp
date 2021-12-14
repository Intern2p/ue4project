// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefenseGameMode.h"
#include "DefenderCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/ConstructorHelpers.h"

ATowerDefenseGameMode::ATowerDefenseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MyBPClasses/BP_DefenderCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
