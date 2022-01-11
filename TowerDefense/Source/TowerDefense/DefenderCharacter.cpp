// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenderCharacter.h"
#include "TowerDefense/SpawnElements/Equipments/Weapon.h"
#include "Inventory.h"
#include "DrawDebugHelpers.h"
#include "BulletShot.h"

// Sets default values
ADefenderCharacter::ADefenderCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	bDead = false;
	bHasWeapon = false;
	MaxHealth = 50.f;

}

// Called when the game starts or when spawned
void ADefenderCharacter::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Health %f"), MaxHealth));
	CurHealth = MaxHealth;
	if (WeaponClass)
	{
		bHasWeapon = true;

		FActorSpawnParameters SpawnParams;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FTransform WeaponTransform;
		WeaponTransform.SetLocation(FVector::ZeroVector);
		WeaponTransform.SetRotation(FQuat(FRotator::ZeroRotator));

		WeaponPickup = GetWorld()->SpawnActor<AWeapon>(WeaponClass, WeaponTransform, SpawnParams);
		if (WeaponPickup)
		{
			WeaponPickup->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("s_hand_r"));
		}
	}
}

// Called every frame
void ADefenderCharacter::OnFire()
{
	//WeaponPickup->Fire();
	if (WeaponClass != nullptr && ProjectileClass != nullptr)
	{
		//UWorld* const World = GetWorld();
		//if (World != nullptr)
		//{
		//	const FRotator SpawnRotation = GetControlRotation();// WeaponPickup->GetActorRotation(); //
		//	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		//	const FVector SpawnLocation = WeaponPickup->GetActorLocation() + SpawnRotation.RotateVector(GunOffset);// GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		//	// Set Spawn Collision Handling Override
		//	FActorSpawnParameters ActorSpawnParams;
		//	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//	// spawn the projectile at the muzzle
		//	World->SpawnActor<ABulletShot>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		//}

		// try and play the sound if specified
		//if (FireSound != nullptr)
		//{
		//	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		//}

		//// try and play a firing animation if specified
		//if (FireAnimation != nullptr)
		//{
		//	// Get the animation object for the arms mesh
		//	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		//	if (AnimInstance != nullptr)
		//	{
		//		AnimInstance->Montage_Play(FireAnimation, 1.f);
		//	}
		//}


		FHitResult OutHit;
		FVector Start = WeaponPickup->GetActorLocation();

		FVector ForwardVector = FollowCamera->GetForwardVector();
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("ForwardVector x = %f; y = %f; z = %f"), ForwardVector.X, ForwardVector.Y, ForwardVector.Z));

			ForwardVector.X += 0.022;
			ForwardVector.Y += 0.08;
			ForwardVector.Z += 0.147;

			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("ForwardVector x = %f; y = %f; z = %f"), ForwardVector.X, ForwardVector.Y, ForwardVector.Z));
		}*/
		FVector End = ((ForwardVector * 1000.f) + Start);
		//FVector End = ;
		FCollisionQueryParams CollisionParams;

		DrawDebugLine(GetWorld(), Start, End, FColor::Green, true);

		bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
		if (isHit)
		{
			if (OutHit.bBlockingHit)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hiting %s"), *OutHit.GetActor()->GetName()));

					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point %s"), *OutHit.ImpactPoint.ToString()));

					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Normal %s"), *OutHit.ImpactNormal.ToString()));
				}
			}
		}
	}
}

//bool ADefenderCharacter::HasWeapon()
//{
//	return bHasWeapon;
//}

// Called every frame
void ADefenderCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

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

}


void ADefenderCharacter::MoveForward(float Axis)
{
	if (!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void ADefenderCharacter::MoveRight(float Axis)
{
	if (!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void ADefenderCharacter::Damage()
{
	if (!bDead)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Health %f"), CurHealth));
		CurHealth -= WeaponPickup->Damage;
		if (CurHealth <= 0)
		{
			CurHealth = 0;
			Die();
		}
	}
	// ? declare dynamic multicast delegate
}

void ADefenderCharacter::Die()
{
	bDead = true;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("DIE"), CurHealth));

	//WeaponPickup->SetLifeSpan(1.f);
	//SetLifeSpan(1.f);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	// Get the animation object for the die
	/*if (AnimDieInstance != nullptr)
	{
		AnimDieInstance->Montage_Play(FireAnimation, 1.f);
	}*/
}


/*INVENTORY*/

void ADefenderCharacter::PickUp(ASpawnElement* PickUpElement)
{
	//Inventory.Add(PickUpElement);
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("overlap2")));
}

