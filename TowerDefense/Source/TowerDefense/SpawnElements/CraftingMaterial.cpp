// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingMaterial.h"

ACraftingMaterial::ACraftingMaterial()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//RootComponent = StaticMesh;
	StaticMesh->SetupAttachment(RootComponent);
}
