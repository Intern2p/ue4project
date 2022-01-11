// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefense/SpawnElements/CharacterEquipment.h"
#include "TowerDefense/SpawnElements/CraftingMaterial.h"
#include "Armor.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AArmor : public ACharacterEquipment
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Specifications")
	TSubclassOf<ACraftingMaterial> Material;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Specifications")
	float BlockingDamage;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Specifications")
	int NecessaryCountMaterials;
};
