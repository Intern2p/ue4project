// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "Containers/Array.h"

#include "DefenderCharacter.generated.h"

class AWeapon;
class USkeletalMeshComponent;
class ABulletShot;
class ASpawnElement;
class UInventory;
UCLASS()
class TOWERDEFENSE_API ADefenderCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefenderCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnFire();
	void Die();

	AWeapon* WeaponPickup;
public:	

	/** Projectile class to spawn */
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = Weapon)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = Weapon)
	bool bHasWeapon;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = Weapon)
	TSubclassOf<AActor> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UInventory* Inventory;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = Actor)
	float MaxHealth;
	float CurHealth;

	bool bDead;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Damage();
	void PickUp(ASpawnElement* PickUpElement);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};


