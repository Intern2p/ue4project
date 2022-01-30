// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerDefense/SpawnElements/CharacterEquipment.h"
#include "TowerDefense/SpawnElements/CraftingMaterial.h"
#include "Armor.generated.h"

class ACraftingMaterial;
UCLASS()
class TOWERDEFENSE_API AArmor : public ACharacterEquipment
{
	GENERATED_BODY()

public:
	AArmor();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = ArmorMaterial)
	TSubclassOf<ACraftingMaterial> ClassMaterial;

	UFUNCTION()
	void CreateNewArmor(UClass* NewMaterial);

	UFUNCTION()
	float BlockDamage(float Damage);

	UFUNCTION()
	ACraftingMaterial* GetMaterial();

	UFUNCTION()
	float GetBlockingDamage();

private:
	ACraftingMaterial* Material;
};
