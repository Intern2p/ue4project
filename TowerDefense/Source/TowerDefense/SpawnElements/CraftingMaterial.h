// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnElement.h"
#include "CraftingMaterial.generated.h"

class ADefenderCharacter;
class UInventoryComponent;
UCLASS()
class TOWERDEFENSE_API ACraftingMaterial : public ASpawnElement
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACraftingMaterial();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "StaticMesh")
		UStaticMeshComponent* StaticMesh;

	virtual FString GetMaterialName();
	virtual float GetArmorBlockingDamage();
	virtual int GetArmorNecessaryCountMaterials();
	virtual void PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory);
};
