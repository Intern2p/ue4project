// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class AWood;
class AStone;
class AMetal;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	TArray<AWood*> Wood;
	TArray<AStone*> Stone;
	TArray<AMetal*> Metal;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int MaxWeight;
	int CurWeight;
	
	UFUNCTION()
	int GetCountWood();

	UFUNCTION()
	int GetCountStone();

	UFUNCTION()
	int GetCountMetal();



};
