// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TowerDefense/Characters/BaseCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100;
	CurrentHealth = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if (Owner)
	{
		 Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	ABaseCharacter* Player = Cast<ABaseCharacter>(DamagedActor);
	if (Player != nullptr)
	{
		/* Block armory damage */
		Damage = Player->BlockPlayerDamage(Damage);
		if (Damage <= 0)
		{
			return;
		}
		CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, DefaultHealth);

		if (CurrentHealth <= 0.f)
		{
			Player->Die();
		}
	}
}

void UHealthComponent::Regenerate()
{
	CurrentHealth = DefaultHealth;
}