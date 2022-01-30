// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Wood.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Stone.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Metal.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	/*CountWood = 0;
	CountStone = 0;
	CountMetal = 0;*/
	CountMaterials.Empty();

}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("countElements %d"), CountMaterials.Num()));
	
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Add +1")));
	}
	else
	{
		CountMaterials.Add(MaterialName, Count);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Add New")));
	}
	
}
