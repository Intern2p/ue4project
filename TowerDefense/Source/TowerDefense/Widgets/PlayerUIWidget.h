// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUIWidget.generated.h"

class UInventoryComponent;
class ADefenderCharacter;
UCLASS()
class TOWERDEFENSE_API UPlayerUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	//void SetInventory(UInventoryComponent* CharInventory) { Inventory = CharInventory; }
	//void SetOwnerCharacter(ADefenderCharacter* Char, UInventoryComponent* CharInventory) { OwnerCharacter = Char; Inventory = CharInventory }

protected:

	virtual void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	ADefenderCharacter* OwnerCharacter;

private:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHealthLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxHealthLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountWoodLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountStoneLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CountMetalLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TypeArmorLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BlockDamageLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ToolTipLabel;

public:

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	bool isActiveToolTip;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	ESlateVisibility VisibleToolTip;

};
