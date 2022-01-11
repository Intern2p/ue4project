// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefenseGameMode.h"
#include "TowerDefenseCharacter.h"
#include "UObject/ConstructorHelpers.h"

//1 - убрать черный фон у прицела
//2 - выстрел лучше реализовать через projectile или trace? Если trace - то как сделать луч в центр и коллизию с персонажем.
//3 - логика подбора предмета (на overlap предмет становиться возможным поднять, на кнопку f персонаж поднимает предмет) вопрос - как персонаж поймет какой предмет он поднял

ATowerDefenseGameMode::ATowerDefenseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
