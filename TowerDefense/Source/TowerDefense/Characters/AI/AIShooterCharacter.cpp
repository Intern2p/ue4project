// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooterCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/WidgetComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIControllerShooterCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "TowerDefense/Components/HealthComponent.h"
#include "TowerDefense/TargetLocation.h"
#include "TowerDefense/Widgets/HealthBarWidget.h"
#include "TowerDefense/SpawnElements/Equipments/Weapon.h"
#include "TowerDefense/SpawnElements/CraftingMaterial.h"

// Sets default values
AAIShooterCharacter::AAIShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Initializing our Pawn Sensing comp and our behavior tree reference
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	BehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("BehaviorTreeReference"));

	bCanSeePlayer = false;
	bInFinallyLocation = false;

	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void AAIShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIShooterCharacter::OnSeePawn);
	}

	UHealthBarWidget* HealthBar = Cast<UHealthBarWidget>(HealthWidgetComp->GetUserWidgetObject());
	if (HealthBar)
	{
		HealthBar->SetOwnerCharacter(this);
	}
	HealthWidgetComp->SetVisibility(false);
}


void AAIShooterCharacter::OnSeePawn(APawn* Pawn)
{
	if (Pawn != this && isAlive)
	{
		AAIControllerShooterCharacter* ControllerShooterCharacter = Cast<AAIControllerShooterCharacter>(GetController());

		ADefenderCharacter* Char = Cast<ADefenderCharacter>(Pawn);

		if (ControllerShooterCharacter && Char && Char->isAlive)
		{
			bCanSeePlayer = true;
			VisiblePlayer = Pawn;
			HealthWidgetComp->SetVisibility(true);

			//Updates our target based on what we've heard.
			ControllerShooterCharacter->SetTargetLocation(Pawn->GetActorLocation());
			ControllerShooterCharacter->StopMovement();

			ControllerShooterCharacter->SetPlayerSighted(true);

			FVector EndLocation = VisiblePlayer->GetActorLocation();
			FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EndLocation);
			FVector EyeLocation;
			FRotator EyeRotation;
			GetActorEyesViewPoint(EyeLocation, EyeRotation);
			FollowCamera->SetWorldRotation(PlayerRot);

			SetActorRotation(FRotator(GetActorRotation().Pitch, PlayerRot.Yaw, PlayerRot.Roll));

			FTimerHandle TimerHandle;
			FTimerDelegate TimerDel;
			TimerDel.BindUFunction(this, FName("CantSeePlayer"), ControllerShooterCharacter);
			GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 2.f, false);
			
		}
	}
}

void AAIShooterCharacter::CantSeePlayer(AAIControllerShooterCharacter* ControllerShooterCharacter)
{
	HealthWidgetComp->SetVisibility(false);
	ControllerShooterCharacter->SetPlayerSighted(false);
	ControllerShooterCharacter->SetTargetLocation(ControllerShooterCharacter->FinallyLocation->GetActorLocation());
}

void AAIShooterCharacter::Die()
{
	Super::Die();
	WeaponPickup->SetLifeSpan(5.f);

	if (bInFinallyLocation)
	{
		AAIControllerShooterCharacter* ControllerShooterCharacter = Cast<AAIControllerShooterCharacter>(GetController());
		if (ControllerShooterCharacter)
		{
			ControllerShooterCharacter->FinallyLocation->CountEnemiesAtLocation = FMath::Clamp(ControllerShooterCharacter->FinallyLocation->CountEnemiesAtLocation - 1, 0, 9999);
			if (ControllerShooterCharacter->FinallyLocation->CountEnemiesAtLocation <= 0)
				ControllerShooterCharacter->FinallyLocation->isDestruct = false;
		}
	}

	SetLifeSpan(5.f);
	SpawnCraftingMaterial();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AAIShooterCharacter::SpawnCraftingMaterial()
{
	if ( ClassDropMaterial.Num() > 0 )
	{
		int StartRange = 0;
		int EndRange = ClassDropMaterial.Num() - 1;

		int index = FMath::RandRange(StartRange, EndRange);
		GetWorld()->SpawnActor<ACraftingMaterial>(ClassDropMaterial[index], GetActorLocation(), GetActorRotation());
	}
}
