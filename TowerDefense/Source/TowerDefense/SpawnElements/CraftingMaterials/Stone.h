// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefense/SpawnElements/CraftingMaterial.h"
#include "Stone.generated.h"

class ADefenderCharacter;
class UInventoryComponent;
UCLASS()
class TOWERDEFENSE_API AStone : public ACraftingMaterial
{
	GENERATED_BODY()

	AStone();
private:
	// STATS FOR ARMOR 
	float ArmorBlockingDamage;
	int ArmorNecessaryCountMaterials;

public:
	float GetArmorBlockingDamage() override;
	int GetArmorNecessaryCountMaterials() override;
	void PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory) override;
};


