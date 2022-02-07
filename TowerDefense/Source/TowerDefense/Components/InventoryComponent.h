// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class ACraftingMaterial;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	
	UFUNCTION()
	int GetCountMaterial(FString MaterialName);

	UFUNCTION()
	void AddCountMaterial(int count, FString MaterialName);

private:
	TMap<FString, int> CountMaterials;

};
