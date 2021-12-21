// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerTriggerBox.h"
// include draw debu helpers header file
#include "DrawDebugHelpers.h"
#include "PlacableActor.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"

void ASpawnerTriggerBox::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ASpawnerTriggerBox::PlacableActorSpawn, 1.f, true);
}

ASpawnerTriggerBox::ASpawnerTriggerBox()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ASpawnerTriggerBox::PlacableActorSpawn()
{
	//GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, TEXT("Hello"));

	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ActorToSpawn, FoundEnemies);
	int CurrentCount = 0;
	for (AActor* TActor : FoundEnemies)
	{
		APlacableActor* MyActor = Cast<APlacableActor>(TActor);
		if (MyActor != nullptr)
			CurrentCount++;
	}

	if (ActorToSpawn != nullptr && MaxCountActors > 0 && CurrentCount < MaxCountActors )
	{
		const FVector Location = GetActorLocation();
		//Location.X;	-265
		//Location.Y;	-13
		//Location.Z;	525

		const FVector Extent = GetComponentsBoundingBox().GetExtent();
		//Extent.X;	1970
		//Extent.Y;	1955
		//Extent.Z;	350

		const FRotator Rotation = GetActorRotation();

		//UE_LOG(LogTemp, Display, TEXT("Hello %.1f"), Extent.X);

		float CoordX = FMath::RandRange(Location.X - Extent.X / 2.f, Location.X + Extent.X / 2.f);
		float CoordY = FMath::RandRange(Location.Y - Extent.Y / 2.f, Location.Y + Extent.Y / 2.f);
		float CoordZ = FMath::RandRange(Location.Z - Extent.Z / 2.f, Location.Z + Extent.Z / 2.f);

		FVector LocationSpawnObject = FVector(CoordX, CoordY, CoordZ);

		GetWorld()->SpawnActor<APlacableActor>(ActorToSpawn, LocationSpawnObject, Rotation);

	}
}

void ASpawnerTriggerBox::PostInitProperties()
{
	Super::PostInitProperties();

	CalculateValues();
}

void ASpawnerTriggerBox::CalculateValues()
{
	if (MaxCountActors > 100)
		MaxCountActors = 100;
	if (MaxCountActors < 0)
		MaxCountActors *= -1;
}

#if WITH_EDITOR
void ASpawnerTriggerBox::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	CalculateValues();
}
#endif