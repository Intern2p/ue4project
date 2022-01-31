// Fill out your copyright notice in the Description page of Project Settings.


#include "Armor.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Wood.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Stone.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Metal.h"

AArmor::AArmor()
{
	if (ClassMaterial)
		Material = GetWorld()->SpawnActor<ACraftingMaterial>(ClassMaterial);
}

float AArmor::BlockDamage(float Damage)
{
	if (ClassMaterial)
	{
		Damage -= Material->GetArmorBlockingDamage();
	}
	return Damage;
}

void AArmor::CreateNewArmor(UClass* NewMaterial)
{
	ClassMaterial = NewMaterial;
	if (ClassMaterial)
		Material = GetWorld()->SpawnActor<ACraftingMaterial>(ClassMaterial);
}

ACraftingMaterial* AArmor::GetMaterial()
{
	if (ClassMaterial)
		return Material;
	return nullptr;
}


float AArmor::GetBlockingDamage()
{
	if (ClassMaterial)
		return Material->GetArmorBlockingDamage();
	return 0;
}