// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefense/SpawnElements/CraftingMaterial.h"
#include "Wood.generated.h"

class ADefenderCharacter;
class UInventoryComponent;
UCLASS()
class TOWERDEFENSE_API AWood : public ACraftingMaterial
{
	GENERATED_BODY()

	AWood();
private:
	// STATS FOR ARMOR 
	float ArmorBlockingDamage;
	int ArmorNecessaryCountMaterials;

public:
	FString GetMaterialName() override;
	float GetArmorBlockingDamage() override;
	int GetArmorNecessaryCountMaterials() override;

	void PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory) override;
};
