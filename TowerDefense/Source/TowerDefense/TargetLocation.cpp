// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetLocation.h"
#include "TowerDefense/Characters/AI/AIShooterCharacter.h"
#include "FPSHUD.h"
#include "Kismet/GameplayStatics.h"

ATargetLocation::ATargetLocation()
{

}

void ATargetLocation::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ATargetLocation::OnOverlapBegin);
}

void ATargetLocation::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if ((OverlappedActor != nullptr) && (OtherActor != this) && (OtherActor != nullptr))
	{
		AAIShooterCharacter* AICharacter = Cast<AAIShooterCharacter>(OtherActor);
		if (AICharacter != nullptr)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Game Over")));
			APawn* Character = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
			ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(Character);
			MyCharacter->isAlive = false;

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			AFPSHUD* TheHUD = Cast<AFPSHUD>(PlayerController->GetHUD());
			TheHUD->ShowGameOverWidget();

			MyCharacter->DetachFromControllerPendingDestroy();
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true;
			PlayerController->bEnableMouseOverEvents = true;

		}
	}
}