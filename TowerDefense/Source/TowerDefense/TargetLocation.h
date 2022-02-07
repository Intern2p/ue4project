// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TargetLocation.generated.h"

UCLASS()
class TOWERDEFENSE_API ATargetLocation : public ATriggerBox
{
	GENERATED_BODY()

	ATargetLocation();

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Destruct)
	bool isDestruct;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Destruct)
	float PercentDestruction;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Destruct)
	int CountEnemiesAtLocation;

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void GameOver();
};
