// Copyright Epic Games, Inc. All Rights Reserved.

#include "HomeworkUEGameMode.h"
#include "HomeworkUEHUD.h"
#include "HomeworkUECharacter.h"
#include "UObject/ConstructorHelpers.h"

AHomeworkUEGameMode::AHomeworkUEGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AHomeworkUEHUD::StaticClass();
}
