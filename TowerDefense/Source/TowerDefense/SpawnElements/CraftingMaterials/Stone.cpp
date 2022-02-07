// Fill out your copyright notice in the Description page of Project Settings.


#include "Stone.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "TowerDefense/Components/InventoryComponent.h"

AStone::AStone()
{
	// STATS FOR ARMOR 
	ArmorBlockingDamage = 20.f;
	ArmorNecessaryCountMaterials = 6;
}

float AStone::GetArmorBlockingDamage()
{
	return ArmorBlockingDamage;
}

int AStone::GetArmorNecessaryCountMaterials()
{
	return ArmorNecessaryCountMaterials;
}

void AStone::PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory)
{
	if (Inventory)
	{
		Inventory->AddCountMaterial(1, AStone::StaticClass()->GetName());
		if (Inventory->GetCountMaterial(AStone::StaticClass()->GetName()) >= ArmorNecessaryCountMaterials)
		{
			Player->CreateCharacterNewArmor(AStone::StaticClass());
		}
	}
}