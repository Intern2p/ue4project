// Fill out your copyright notice in the Description page of Project Settings.


#include "Metal.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "TowerDefense/Components/InventoryComponent.h"

AMetal::AMetal()
{
	// STATS FOR ARMOR 
	ArmorBlockingDamage = 30.f;
	ArmorNecessaryCountMaterials = 3;
}

float AMetal::GetArmorBlockingDamage()
{
	return ArmorBlockingDamage;
}

int AMetal::GetArmorNecessaryCountMaterials()
{
	return ArmorNecessaryCountMaterials;
}

void AMetal::PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory)
{
	if (Inventory)
	{
		Inventory->AddCountMaterial(1, AMetal::StaticClass()->GetName());
		if (Inventory->GetCountMaterial(AMetal::StaticClass()->GetName()) >= ArmorNecessaryCountMaterials)
		{
			Player->CreateCharacterNewArmor(AMetal::StaticClass());
		}
	}
}