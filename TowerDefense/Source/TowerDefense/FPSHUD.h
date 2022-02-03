// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "FPSHUD.generated.h"

class UUserWidget;
UCLASS()
class TOWERDEFENSE_API AFPSHUD : public AHUD
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;

public:
	// This will be drawn at the center of the screen.
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<class UUserWidget>> AllUIWidgets;

	UPROPERTY(EditDefaultsOnly)
	class TSubclassOf<UUserWidget> GameOverWidget;

	/*UPROPERTY(EditDefaultsOnly)
	class TSubclassOf<UUserWidget> NumStageWidget;*/

	UFUNCTION()
	void ShowGameOverWidget();

	//UFUNCTION()
	//void ShowStageWaveWidget();
		
	// Primary draw call for the HUD.
	virtual void DrawHUD() override;

private:

	//UUserWidget* WidgetStageWave;

//	UFUNCTION()
	//void HideStageWaveWidget();
};
