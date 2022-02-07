// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "TowerDefense/SpawnElements/Equipments/Weapon.h"
#include "TowerDefense/SpawnElements/Equipments/Armor.h"
#include "TowerDefense/SpawnElements/CraftingMaterial.h"
#include "TowerDefense/Components/HealthComponent.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	isAlive = true;
	
	/* Spawn Weapon */
	if (WeaponClass)
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
	}
	else
	{
		bHasWeapon = false;
	}

	/* Spawn Armor (in future will has mesh) */
	ArmorWear = GetWorld()->SpawnActor<AArmor>();
	if (ArmorClass)
	{
		ArmorWear->CreateNewArmor(ArmorClass);
	}

}

void ABaseCharacter::OnFire()
{
	if (WeaponClass != nullptr && isAlive)
	{
		WeaponPickup->Fire();
	}
}

void ABaseCharacter::Die() {
	isAlive = false;
}

float ABaseCharacter::BlockPlayerDamage(float Damage)
{
	if (ArmorWear)
		Damage = ArmorWear->BlockDamage(Damage);
	return Damage;
}

FVector ABaseCharacter::GetPawnViewLocation() const
{
	if (FollowCamera)
	{
		return FollowCamera->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}

float ABaseCharacter::GetHealth()
{
	if (Health)
		return Health->CurrentHealth;
	return 0;
}

float ABaseCharacter::GetMaxHealth() 
{
	if (Health)
		return Health->DefaultHealth;
	return 0;
}

FString ABaseCharacter::GetArmorMaterial()
{
	if (ArmorClass)
		return ArmorWear->MaterialName;
	return "";
}

float ABaseCharacter::GetArmorBlockingDamage()
{
	if (ArmorClass)
		return ArmorWear->BlockDamageValue;
	return 0;
}


