// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacableActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APlacableActor::APlacableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlacableActor"));
	RootComponent = StaticMesh;

}

// Called when the game starts or when spawned
void APlacableActor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(FMath::RandRange(MinTimeLifeSec, MaxTimeLifeSec));
}

// Called every frame
void APlacableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlacableActor::PostInitProperties()
{
	Super::PostInitProperties();

	CalculateValues();
}

void APlacableActor::CalculateValues()
{
	if (MaxTimeLifeSec < 0)
		MaxTimeLifeSec *= -1;
	if (MinTimeLifeSec < 0)
		MinTimeLifeSec *= -1;
}

#if WITH_EDITOR
void APlacableActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	CalculateValues();
}
#endif
