// Fill out your copyright notice in the Description page of Project Settings.


#include "Metal.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "TowerDefense/Components/InventoryComponent.h"

AMetal::AMetal()
{
	// STATS FOR ARMOR 
	ArmorBlockingDamage = 25.f;
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

FString AMetal::GetMaterialName()
{
	return AMetal::StaticClass()->GetName();
}

void AMetal::PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory)
{
	if (Inventory)
	{
		Inventory->AddCountMaterial(1, AMetal::StaticClass()->GetName());
		if (Inventory->GetCountMaterial(AMetal::StaticClass()->GetName()) >= ArmorNecessaryCountMaterials)
		{
			Player->CreateCharacterNewArmor(AMetal::StaticClass());
			Inventory->AddCountMaterial(ArmorNecessaryCountMaterials*(-1), AMetal::StaticClass()->GetName());
		}
	}
}