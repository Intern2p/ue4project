// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ue4ProjectHUD.generated.h"

UCLASS()
class Aue4ProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	Aue4ProjectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

