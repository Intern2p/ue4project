// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenderCharacter.h"
#include "DrawDebugHelpers.h"
#include "TowerDefense/Components/InventoryComponent.h"
#include "TowerDefense/Components/HealthComponent.h"
#include "TowerDefense/SpawnElements/SpawnElement.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "TowerDefense/Widgets/PlayerUIWidget.h"
#include "TowerDefense/FPSHUD.h"
#include "TowerDefense/SpawnElements/Equipments/Armor.h"
#include "TowerDefense/TowerDefender_GameMode.h"

#define AddToInventoryToolTip "Added to Inventory"
#define CreateArmorToolTip "New Armor Was Created"

// Sets default values
ADefenderCharacter::ADefenderCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void ADefenderCharacter::BeginPlay()
{
	Super::BeginPlay();
	RespawnLocation = GetActorLocation();
}

// Called to bind functionality to input
void ADefenderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADefenderCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ADefenderCharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADefenderCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADefenderCharacter::MoveRight);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADefenderCharacter::OnFire);
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ADefenderCharacter::PickUpItem);

}

void ADefenderCharacter::MoveForward(float Axis)
{
	if (isAlive)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void ADefenderCharacter::Jump()
{
	if (isAlive)
	{
		bPressedJump = true;
		JumpKeyHoldTime = 0.0f;
	}
}

void ADefenderCharacter::StopJumping()
{
	if (isAlive)
	{
		bPressedJump = false;
		ResetJumpState();
	}
}

void ADefenderCharacter::MoveRight(float Axis)
{
	if (isAlive)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

/*INVENTORY*/

void ADefenderCharacter::PickUpItem()
{
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector EyeLocation = camManager->GetCameraLocation();
	FVector ForwardVector = camManager->GetCameraRotation().Vector();

	FVector TraceEnd = EyeLocation + ForwardVector*300;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	FHitResult Hit;
	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), EyeLocation, TraceEnd, 300.f, UEngineTypes::ConvertToTraceType(ECC_SpawnElements), false, TArray<AActor*> { this }, EDrawDebugTrace::None, Hit, true);

	AActor* HitActor = Hit.GetActor();
	ASpawnElement* SpawnElement = Cast<ASpawnElement>(HitActor);
	if (SpawnElement != nullptr) {

		SpawnElement->PickUpElement(this, this->Inventory);
		SpawnElement->Destroy();

		if (ShowMessage != CreateArmorToolTip)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle);
			GetWorldTimerManager().SetTimer(TimerHandle, this, &ADefenderCharacter::ClearToolTip, 4.f, false);

			ShowMessage = AddToInventoryToolTip;
		}
	}
}

void ADefenderCharacter::ClearToolTip()
{	
	ShowMessage.Empty();
}

void ADefenderCharacter::Die()
{
	Super::Die();

	FTimerHandle TimerHandleResp;
	GetWorldTimerManager().SetTimer(TimerHandleResp, this, &ADefenderCharacter::Respawn, 5.f, false);
}
void ADefenderCharacter::Respawn()
{
	SetActorLocation(RespawnLocation);
	isAlive = true;
	Health->Regenerate();
}

void ADefenderCharacter::CreateCharacterNewArmor(UClass* ClassArmor)
{
	ArmorClass = ClassArmor;
	ArmorWear->CreateNewArmor(ClassArmor);

	GetWorldTimerManager().ClearTimer(TimerHandle);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADefenderCharacter::ClearToolTip, 6.f, false);
	ShowMessage = CreateArmorToolTip;
}