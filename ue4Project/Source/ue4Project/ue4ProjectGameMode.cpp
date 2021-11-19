// Copyright Epic Games, Inc. All Rights Reserved.

#include "ue4ProjectGameMode.h"
#include "ue4ProjectHUD.h"
#include "ue4ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

Aue4ProjectGameMode::Aue4ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Aue4ProjectHUD::StaticClass();
}
