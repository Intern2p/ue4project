// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"

#include "BaseCharacter.generated.h"

class AWeapon;
class AArmor;
class ACraftingMaterial;
class UHealthComponent;
class USkeletalMeshComponent;
UCLASS()
class TOWERDEFENSE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AWeapon* WeaponPickup;
	AArmor* ArmorWear;

public:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Health)
	bool isAlive;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Equipment)
	bool bHasWeapon;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Equipment)
	TSubclassOf<AActor> WeaponClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Equipment)
	TSubclassOf<AActor> ArmorClass;

	UHealthComponent* Health;

	UFUNCTION(BlueprintCallable)
	void OnFire();

	UFUNCTION(BlueprintCallable)
	float BlockPlayerDamage(float Damage);

	UFUNCTION()
	float GetHealth();

	UFUNCTION()
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	FString GetArmorMaterial();

	UFUNCTION(BlueprintCallable)
	float GetArmorBlockingDamage();

	virtual void Die();
	virtual FVector GetPawnViewLocation() const;
};

