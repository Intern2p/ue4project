// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnElement.h"
#include "TowerDefense/DefenderCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASpawnElement::ASpawnElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = MeshComp;*/

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("BoxCollider"));
	SphereCollider->InitSphereRadius(80.0f);
	SphereCollider->SetCollisionProfileName("Trigger");
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpawnElement::OnOverlapBegin);
	SphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//RootComponent = SphereCollider;
	//SphereCollider->SetupAttachment(RootComponent);

	bPickUpable = false;
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
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 80.0f, 20, FColor::Purple, false, -1, 0, 1);
}

void ASpawnElement::OnOverlapBegin(UPrimitiveComponent* OverlapComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if the OtherActor is not me and if it is not NULL
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//try to cast
		ADefenderCharacter* MyCharacter = Cast<ADefenderCharacter>(OtherActor);
		if (MyCharacter != nullptr)
		{
			bPickUpable = true;
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Press E to pick up")));
			//MyCharacter->PickUp(this);
			//Destroy();
		}

	}
	/*ACharacter* MyCharacter = Cast<ACharacter>(OtherActor);
	if ((OtherActor != nullptr) && (MyCharacter != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Destroy();
	}*/
}