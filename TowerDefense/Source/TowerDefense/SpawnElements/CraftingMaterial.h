// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnElement.h"
#include "CraftingMaterial.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ACraftingMaterial : public ASpawnElement
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACraftingMaterial();

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "StaticMesh")
		UStaticMeshComponent* StaticMesh;
};
