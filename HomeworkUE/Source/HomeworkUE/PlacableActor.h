// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlacableActor.generated.h"

UCLASS()
class HOMEWORKUE_API APlacableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlacableActor();

	static int CounterActors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "StaticMesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Actor")
	float MinTimeLifeSec;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Actor")
	float MaxTimeLifeSec;

	UFUNCTION(BlueprintCallable)
	void CalculateValues();

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	void PostInitProperties();

};
