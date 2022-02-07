// Fill out your copyright notice in the Description page of Project Settings.


#include "Wood.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "TowerDefense/Components/InventoryComponent.h"

AWood::AWood()
{
	// STATS FOR ARMOR 
	ArmorBlockingDamage = 10.f;
	ArmorNecessaryCountMaterials = 7;
}

float AWood::GetArmorBlockingDamage()
{
	return ArmorBlockingDamage;
}

int AWood::GetArmorNecessaryCountMaterials()
{
	return ArmorNecessaryCountMaterials;
}

FString AWood::GetMaterialName()
{
	return AWood::StaticClass()->GetName();
}

void AWood::PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory)
{
	if (Inventory)
	{
		Inventory->AddCountMaterial(1, AWood::StaticClass()->GetName());
		if (Inventory->GetCountMaterial(AWood::StaticClass()->GetName()) >= ArmorNecessaryCountMaterials)
		{
			Player->CreateCharacterNewArmor(AWood::StaticClass());
			Inventory->AddCountMaterial(ArmorNecessaryCountMaterials * (-1), AWood::StaticClass()->GetName());

		}
	}
}