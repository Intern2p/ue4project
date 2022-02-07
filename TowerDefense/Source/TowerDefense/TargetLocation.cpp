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
	CountEnemiesAtLocation = 0;
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
			CountEnemiesAtLocation++; 
			AICharacter->bInFinallyLocation = true;
		}
	}
}

void ATargetLocation::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((OverlappedActor != nullptr) && (OtherActor != this) && (OtherActor != nullptr))
	{
		AAIShooterCharacter* AICharacter = Cast<AAIShooterCharacter>(OtherActor);
		if (AICharacter != nullptr && AICharacter->isAlive == true)
		{
			CountEnemiesAtLocation = FMath::Clamp(CountEnemiesAtLocation - 1, 0, 9999);
			if (CountEnemiesAtLocation <= 0)
				isDestruct = false;
			AICharacter->bInFinallyLocation = false;
		}
	}
}
// Called every frame
void ATargetLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isDestruct)
	{
		PercentDestruction = FMath::Clamp(PercentDestruction + DeltaTime * 5, 0.f, 100.f);
		if (PercentDestruction >= 100.f)
		{
			ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			if (MyCharacter)
				MyCharacter->isAlive = false;
			GameOver();
		}
	}
	else
	{
		PercentDestruction = 0.f;
	}
}

void ATargetLocation::GameOver()
{
	ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (MyCharacter)
		MyCharacter->DetachFromControllerPendingDestroy();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (PlayerController)
	{
		AFPSHUD* TheHUD = Cast<AFPSHUD>(PlayerController->GetHUD());
		if (TheHUD)
			TheHUD->ShowGameOverWidget();

		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
}