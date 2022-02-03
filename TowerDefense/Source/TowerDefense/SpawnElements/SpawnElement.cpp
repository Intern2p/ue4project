// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnElement.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "TowerDefense/Components/InventoryComponent.h"
#include "DrawDebugHelpers.h"

#define PickUpToolTip "Press E to Pick Up"

// Sets default values
ASpawnElement::ASpawnElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("BoxCollider"));
	SphereCollider->InitSphereRadius(330.0f);
	SphereCollider->SetCollisionProfileName("Trigger");
	RootComponent = SphereCollider;
	//SphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void ASpawnElement::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpawnElement::OnOverlapBegin);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &ASpawnElement::OnOverlapEnd);
}

// Called every frame
void ASpawnElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
}

void ASpawnElement::OnOverlapBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ADefenderCharacter* MyCharacter = Cast<ADefenderCharacter>(OtherActor);
		if (MyCharacter != nullptr)
		{
			MyCharacter->ToolTip = PickUpToolTip;
		}
	}
}

void ASpawnElement::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OverlappedComp != nullptr))
	{
		ADefenderCharacter* MyCharacter = Cast<ADefenderCharacter>(OtherActor);
		if (MyCharacter != nullptr)
		{
			if (MyCharacter->ToolTip == PickUpToolTip)
				MyCharacter->ToolTip.Empty();
		}
	}
}
void ASpawnElement::PickUpElement(ADefenderCharacter* Player, UInventoryComponent* Inventory) {};