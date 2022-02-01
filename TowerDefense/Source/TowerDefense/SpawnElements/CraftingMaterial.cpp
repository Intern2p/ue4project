// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingMaterial.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "TowerDefense/Components/InventoryComponent.h"

#define ECC_SpawnElements ECC_GameTraceChannel1

ACraftingMaterial::ACraftingMaterial()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(SphereCollider);
	StaticMesh->SetCollisionResponseToChannel(ECC_SpawnElements, ECollisionResponse::ECR_Block);

	/*StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetSimulatePhysics(true);*/
}

// Called every frame
void ACraftingMaterial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(StaticMesh->GetComponentLocation());
}

float ACraftingMaterial::GetArmorBlockingDamage() { return 0.f; };
int ACraftingMaterial::GetArmorNecessaryCountMaterials() { return 0; };
void ACraftingMaterial::PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory) {};
