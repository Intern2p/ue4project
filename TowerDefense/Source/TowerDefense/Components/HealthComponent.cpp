// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "TowerDefense/Characters/BaseCharacter.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
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

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("taken dammage %f"), CurrentHealth));
	
		if (CurrentHealth <= 0.f)
		{
			Player->Die();
		}
	}
}