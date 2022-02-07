// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetLocation.h"
#include "TowerDefense/Characters/AI/AIShooterCharacter.h"
#include "FPSHUD.h"
#include "Kismet/GameplayStatics.h"

ATargetLocation::ATargetLocation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PercentDestruction = 0.f;
}

void ATargetLocation::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ATargetLocation::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATargetLocation::OnOverlapEnd);
}

void ATargetLocation::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((OverlappedActor != nullptr) && (OtherActor != this) && (OtherActor != nullptr))
	{
		AAIShooterCharacter* AICharacter = Cast<AAIShooterCharacter>(OtherActor);
		if (AICharacter != nullptr && AICharacter->isAlive == true)
		{
			isDestruct = true;
		}
	}
}

void ATargetLocation::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((OverlappedActor != nullptr) && (OtherActor != this) && (OtherActor != nullptr))
	{
		AAIShooterCharacter* AICharacter = Cast<AAIShooterCharacter>(OtherActor);
		if (AICharacter != nullptr)
		{
			isDestruct = false;
		}
	}
}
// Called every frame
void ATargetLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDestruct)
	{
		PercentDestruction += DeltaTime*5;
		if (PercentDestruction >= 100.f)
			GameOver();

	}
	else
	{
		PercentDestruction = 0.f;
	}
}

void ATargetLocation::GameOver()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Game Over")));

	APawn* Character = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(Character);
	//MyCharacter->isAlive = false;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFPSHUD* TheHUD = Cast<AFPSHUD>(PlayerController->GetHUD());
	TheHUD->ShowGameOverWidget();

	//MyCharacter->DetachFromControllerPendingDestroy();
	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;
	PlayerController->bEnableMouseOverEvents = true;
}