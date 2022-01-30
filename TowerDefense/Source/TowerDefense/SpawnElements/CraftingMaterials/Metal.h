// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefense/SpawnElements/CraftingMaterial.h"
#include "Metal.generated.h"

#define ECC_SpawnElements ECC_GameTraceChannel1

class ADefenderCharacter;
class UInventoryComponent;
UCLASS()
class TOWERDEFENSE_API AMetal : public ACraftingMaterial
{
	GENERATED_BODY()

	AMetal();
private:
	// STATS FOR ARMOR 
	float ArmorBlockingDamage;
	int ArmorNecessaryCountMaterials;

public:
	float GetArmorBlockingDamage() override;
	int GetArmorNecessaryCountMaterials() override;

	void PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory) override;
};
