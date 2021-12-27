// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnElement.h"

// Sets default values
ASpawnElement::ASpawnElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = MeshComp;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("BoxCollider"));
	SphereCollider->SetGenerateOverlapEvents(true);
	SphereCollider->InitSphereRadius(1.0f);
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpawnElement::OnOverlapBegin);
	SphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void ASpawnElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnElement::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	//Check if the OtherActor is not me and if it is not NULL
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//try to cast
		Destroy();
	}
}