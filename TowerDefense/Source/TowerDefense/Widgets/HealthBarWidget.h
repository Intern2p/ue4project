// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class AAIShooterCharacter;
UCLASS()
class TOWERDEFENSE_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetOwnerCharacter(AAIShooterCharacter* Char) { OwnerCharacter = Char; }

protected:

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	AAIShooterCharacter* OwnerCharacter;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHealthLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxHealthLabel;
};
