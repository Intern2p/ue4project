// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "TowerDefense/Characters/AI/AIShooterCharacter.h"

void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (OwnerCharacter)
	{
		HealthBar->SetPercent(OwnerCharacter->GetHealth() / OwnerCharacter->GetMaxHealth());

		FNumberFormattingOptions Opts;
		Opts.SetMaximumFractionalDigits(0);
		CurrentHealthLabel->SetText(FText::AsNumber(OwnerCharacter->GetHealth(), &Opts));
		MaxHealthLabel->SetText(FText::AsNumber(OwnerCharacter->GetMaxHealth(), &Opts));
	}
}