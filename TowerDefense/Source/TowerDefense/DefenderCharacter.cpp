// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenderCharacter.h"
#include "Weapon.h"
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

		SkeletalWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, WeaponTransform, SpawnParams);
		if (SkeletalWeapon)
		{
			SkeletalWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("s_hand_r"));
		}
	}
}

// Called every frame
void ADefenderCharacter::OnFire()
{
	//SkeletalWeapon->Fire();

	UWorld* const World = GetWorld();
	if (World != nullptr && ProjectileClass != nullptr)
	{
		const FRotator SpawnRotation = GetControlRotation();// SkeletalWeapon->GetActorRotation(); //
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = SkeletalWeapon->GetActorLocation() + SpawnRotation.RotateVector(GunOffset);// GetActorLocation() + SpawnRotation.RotateVector(GunOffset);
	
		// Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// spawn the projectile at the muzzle
		World->SpawnActor<ABulletShot>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}

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
		CurHealth -= SkeletalWeapon->Damage;
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

	//SkeletalWeapon->SetLifeSpan(1.f);
	//SetLifeSpan(1.f);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
	// Get the animation object for the die
	/*if (AnimDieInstance != nullptr)
	{
		AnimDieInstance->Montage_Play(FireAnimation, 1.f);
	}*/
}