// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Wood.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Stone.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Metal.h"

AArmor::AArmor()
{
	MaterialName = "";
	BlockDamageValue = 0;
}

float AArmor::BlockDamage(float Damage)
{
	Damage -= BlockDamageValue;
	return Damage;
}

void AArmor::CreateNewArmor(UClass* NewMaterial)
{
	if (NewMaterial)
		Material = GetWorld()->SpawnActor<ACraftingMaterial>(NewMaterial);

	if (Material->GetArmorBlockingDamage() > BlockDamageValue)
	{
		BlockDamageValue = Material->GetArmorBlockingDamage();
		MaterialName = Material->GetMaterialName();
	}
	Material->Destroy();
}
