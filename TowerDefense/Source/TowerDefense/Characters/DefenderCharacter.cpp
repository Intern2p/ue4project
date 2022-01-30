// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenderCharacter.h"
#include "DrawDebugHelpers.h"
#include "TowerDefense/Components/InventoryComponent.h"
#include "TowerDefense/SpawnElements/SpawnElement.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "TowerDefense/Widgets/PlayerUIWidget.h"
#include "TowerDefense/FPSHUD.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Metal.h"
#include "TowerDefense/TowerDefender_GameMode.h"

// Sets default values
ADefenderCharacter::ADefenderCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	/*CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));*/

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	//Inventory->AttachTo(RootComponent);
	//if (Inventory)
	//{
	//	AFPSHUD* HUD = Cast<AFPSHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	//	if (HUD)
	//	{
	//		if (HUD->AllUIWidgets.Num() > 0)
	//		{
	//			// Iterate through all widgets
	//			for (TSubclassOf<UUserWidget> widget : HUD->AllUIWidgets)
	//			{
	//				// Create an instance of the widget and add to viewport
	//				UPlayerUIWidget* createdWidget = Cast<UPlayerUIWidget>(widget);
	//				createdWidget->SetOwnerCharacter(this, Inventory);
	//			}
	//		}
	//	}
	//}
	//PlayerUIWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("PlayerUI"));
	//PlayerUIWidgetComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		// If any widgets need to be added

}

// Called when the game starts or when spawned
void ADefenderCharacter::BeginPlay()
{
	Super::BeginPlay();
	//isAlive = true;
	
	/*if (WeaponClass)
	{
		bHasWeapon = true;

		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = this;

		FTransform WeaponTransform;
		WeaponTransform.SetLocation(FVector::ZeroVector);
		WeaponTransform.SetRotation(FQuat(FRotator::ZeroRotator));
		
		WeaponPickup = GetWorld()->SpawnActor<AWeapon>(WeaponClass, WeaponTransform, SpawnParams);
		
		if (WeaponPickup)
		{
			WeaponPickup->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("s_hand_r"));
		}
	}*/

	//{
	//	PlayerUIWidget->SetOwnerCharacter(this);
	//	PlayerUIWidget->SetInventory(this->Inventory);
	//}

}

// Called every frame
/*void ADefenderCharacter::OnFire()
{
	if (WeaponClass != nullptr)
	{
		WeaponPickup->Fire();		
	}
}*/


// Called to bind functionality to input
void ADefenderCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

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

void ADefenderCharacter::PickUpItem()
{
	//UWorld* World = GetWorld();
	//if (World)
	//{
	//	ATowerDefender_GameMode* GameMode = Cast<ATowerDefender_GameMode>(World->GetAuthGameMode());
	//	if (GameMode)
	//	{
	//		GameMode->ToolTipText = "HELLO";
	//		 if (GEngine)
	//			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("change tooltop")));
	//	}
	//}
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector EyeLocation = camManager->GetCameraLocation();
	FVector ForwardVector = camManager->GetCameraRotation().Vector();

	FVector TraceEnd = EyeLocation + ForwardVector*400;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	FHitResult Hit;
	DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, true);

	UKismetSystemLibrary::SphereTraceSingle(GetWorld(), EyeLocation, TraceEnd, 200.f, UEngineTypes::ConvertToTraceType(ECC_SpawnElements), false, TArray<AActor*> { this }, EDrawDebugTrace::ForDuration, Hit, true);
	//if (GetWorld()->LineTraceBySingleChannel(Hit, EyeLocation, TraceEnd, /*COLLISION_WEAPON*/ECC_Visibility, QueryParams))
	//{
		//if (Hit.bBlockingHit)
		//{
			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hiting %s"), *Hit.GetActor()->GetName()));

				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point %s"), *Hit.ImpactPoint.ToString()));

				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Normal %s"), *Hit.ImpactNormal.ToString()));
			}*/

		
			AActor* HitActor = Hit.GetActor();
			ASpawnElement* SpawnElement = Cast<ASpawnElement>(HitActor);
			if (SpawnElement != nullptr) {

				SpawnElement->PickUpElement(this, this->Inventory);

				if (ChangeStateElement.IsBound())
				{
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("broadcast")));

					ChangeStateElement.Broadcast("Added to Inventory");
				}
				SpawnElement->Destroy();
			}
			//UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ForwardVector, Hit, MyOwner->GetInstigatorController(), this, DamageType);
			//Hit.Location
		//}
	//}
}

//void ADefenderCharacter::Die()
//{
//	isAlive = true;
//
//	//WeaponPickup->SetLifeSpan(1.f);
//	//SetLifeSpan(1.f);
//	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
//	GetMesh()->SetSimulatePhysics(true);
//	// Get the animation object for the die
//	/*if (AnimDieInstance != nullptr)
//	{
//		AnimDieInstance->Montage_Play(FireAnimation, 1.f);
//	}*/
//}


/*INVENTORY*/

void ADefenderCharacter::PickUp(ASpawnElement* PickUpElement)
{
	//Inventory.Add(PickUpElement);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("overlap2")));
	

}

void ADefenderCharacter::CanPickUpMessage()
{
	if (ChangeStateElement.IsBound())
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("broadcast")));

		ChangeStateElement.Broadcast("Press E to Pick Up");
	}
}

//FVector ADefenderCharacter::GetPawnViewLocation() const
//{
//	if (FollowCamera)
//	{
//		return FollowCamera->GetComponentLocation();
//	}
//	return Super::GetPawnViewLocation();
//}
//
//void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
//{
//	if (GEngine)
//		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("taken dammage")));
//}

