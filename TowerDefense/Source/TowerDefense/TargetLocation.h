// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATargetLocation : public ATriggerBox
{
	GENERATED_BODY()

	ATargetLocation();

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

};
