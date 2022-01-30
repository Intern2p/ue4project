// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TowerDefense/SpawnElements/CharacterEquipment.h"
#include "Weapon.generated.h"

class UAnimMontage;
class USoundBase;
class UDamageType;
class ABaseCharacter;
UCLASS()
class TOWERDEFENSE_API AWeapon : public ACharacterEquipment
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimSequence* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MeshComp)
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damage)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damage)
	float BulletSpread;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Damage)
	float Damage;

	UFUNCTION()
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};
