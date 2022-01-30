// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToolTipWidget.generated.h"

UCLASS()
class TOWERDEFENSE_API UToolTipWidget : public UUserWidget
{
	GENERATED_BODY()

	void SetToolTipText(FString ToolTip) { ToolTipText = ToolTip; }
protected:

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FString ToolTipText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ToolTipLabel;
};
