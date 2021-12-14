// Fill out your copyright notice in the Description page of Project Settings.


#include "AWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AAWeapon::AAWeapon()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void AAWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAWeapon::Fire()
{
	//MeshComp->PlayAnimation(FireAnimation, false);
}

