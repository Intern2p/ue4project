// Fill out your copyright notice in the Description page of Project Settings.


#include "AIShooterCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIControllerShooterCharacter.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "TowerDefense/TargetLocation.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "TowerDefense/Widgets/HealthBarWidget.h"

// Sets default values
AAIShooterCharacter::AAIShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initializing our Pawn Sensing comp and our behavior tree reference
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	BehaviorTree = CreateDefaultSubobject<UBehaviorTree>(TEXT("BehaviorTreeReference"));

	bCanSeePlayer = false;

	HealthWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AAIShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	//isAlive = true;
	if (PawnSensingComp)
	{
		//Registering the delegate which will fire when we hear something
		//PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIShooterCharacter::OnHearNoise);
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIShooterCharacter::OnSeePawn);
	}

	UHealthBarWidget* HealthBar = Cast<UHealthBarWidget>(HealthWidgetComp->GetUserWidgetObject());
	if (HealthBar)
	{
		HealthBar->SetOwnerCharacter(this);
	}
}

//void AAIShooterCharacter::OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume)
//{
//
//	//AMyAIController* Con = Cast<AMyAIController>(GetController());
//
//	//We don't want to hear ourselves
//	//if (Con && PawnInstigator != this)
//	//{
//		//Updates our target based on what we've heard.
//		//Con->SetSensedTarget(PawnInstigator);
//	//}
//}
void AAIShooterCharacter::OnSeePawn(APawn* Pawn)
{
	if (Pawn != this && isAlive)
	{
		AAIControllerShooterCharacter* ControllerShooterCharacter = Cast<AAIControllerShooterCharacter>(GetController());

		ADefenderCharacter* Char = Cast<ADefenderCharacter>(Pawn);

		if (ControllerShooterCharacter && Char)
		{
			bCanSeePlayer = true;
			VisiblePlayer = Pawn;
			//Updates our target based on what we've heard.
			ControllerShooterCharacter->SetTargetLocation(Pawn->GetActorLocation());
			ControllerShooterCharacter->StopMovement();

			ControllerShooterCharacter->SetPlayerSighted(true);

			FVector EndLocation = VisiblePlayer->GetActorLocation();
			FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EndLocation);
			SetActorRotation(PlayerRot);
			//CameraBoom->SetWorldRotation(PlayerRot);
			//FollowCamera->SetWorldRotation(PlayerRot);
			//ControllerShooterCharacter->TryToFire(ControllerShooterCharacter, Pawn);
			/*if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("see player")));
			FTimerHandle TimerHandle;
			FTimerDelegate  TimerDel;
			TimerDel.BindUFunction(this, FName("CantSeePlayer"), ControllerShooterCharacter);
			GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 5.0f, true);*/
			
		}
	}
}

//void AAIShooterCharacter::CantSeePlayer(AAIControllerShooterCharacter* ControllerShooterCharacter)
//{
//	if (GEngine)
//		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("dont see player")));
//	//AAIControllerShooterCharacter* ControllerShooterCharacter = Cast<AAIControllerShooterCharacter>(GetController());
//	ControllerShooterCharacter->SetPlayerSighted(false);
//	ControllerShooterCharacter->SetTargetLocation(ControllerShooterCharacter->FinallyLocation->GetActorLocation());
//}

// Called every frame
void AAIShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (bCanSeePlayer && VisiblePlayer != nullptr) {

		FVector EndLocation = VisiblePlayer->GetActorLocation();
		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), EndLocation);
		FRotator NewRot = FMath::RInterpTo(GetMesh()->GetComponentRotation(), PlayerRot, DeltaTime, 2);
		SetActorRotation(PlayerRot);
	}*/
}