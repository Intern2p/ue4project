// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AWeapon.generated.h"

UCLASS()
class TOWERDEFENSE_API AAWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AAWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComp)
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FireAnimation)
	class UAnimationAsset* FireAnimation;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void Fire();
};
