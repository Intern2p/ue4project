// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Blueprint/UserWidget.h"
#include "Containers/Array.h"
#include "DefenderCharacter.generated.h"

#define ECC_SpawnElements ECC_GameTraceChannel1

class USkeletalMeshComponent;
class ASpawnElement;
class UInventoryComponent;
class UWidgetComponent;
UCLASS()
class TOWERDEFENSE_API ADefenderCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefenderCharacter();

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint8 bUsingMotionControllers : 1;

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void Jump();
	void StopJumping();
	void PickUpItem();

protected:
	// Called when the game starts or when spawned
	
	virtual void BeginPlay() override;
public:	

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = HealthBar)
	UWidgetComponent* PlayerUIWidgetComp;

	UPROPERTY(EditDefaultsOnly)
	FString ToolTip;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Gameplay)
	FVector RespawnLocation;

	UInventoryComponent* Inventory;

	UFUNCTION(BlueprintCallable)
	void Die() override;

	UFUNCTION(BlueprintCallable)
	void Respawn();

	UFUNCTION(BlueprintCallable)
	void ClearToolTip();

	UFUNCTION(BlueprintCallable)
	void CreateCharacterNewArmor(UClass* ClassArmor);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};

