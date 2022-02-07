// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Wood.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Stone.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Metal.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CountMaterials.Empty();
}


int UInventoryComponent::GetCountMaterial(FString MaterialName)
{
	if (CountMaterials.Contains(MaterialName))
	{
		return CountMaterials[MaterialName];
	}

	return 0;
}

void UInventoryComponent::AddCountMaterial(int Count, FString MaterialName)
{
	if (CountMaterials.Contains(MaterialName))
	{
		CountMaterials[MaterialName] += Count;
	}
	else
	{
		CountMaterials.Add(MaterialName, Count);
	}
	
}
