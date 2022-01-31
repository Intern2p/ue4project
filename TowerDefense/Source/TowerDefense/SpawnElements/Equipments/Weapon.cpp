// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Containers/UnrealString.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/Characters/BaseCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = MeshComp;
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Fire()
{
	//Trace the world, from pawn eyes to croshair location
	 
	AActor* MyOwner = GetOwner(); if (GEngine)
		
	if (MyOwner)
	{
		//float BulletSpread = 0.5f;
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector TraceStart = GetActorLocation();
		FVector ShotDirection = EyeRotation.Vector();

		float HalfRad = FMath::DegreesToRadians(BulletSpread);

		ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);
		FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = true;

		FVector TracerEndPoint = TraceEnd;

		EPhysicalSurface SurfaceType = SurfaceType_Default;
		FHitResult Hit;
		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Green, true);
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, /*COLLISION_WEAPON*/ECC_Visibility, QueryParams))
		{
			if (Hit.bBlockingHit)
			{
				/*if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hiting %s"), *Hit.GetActor()->GetName()));

					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point %s"), *Hit.ImpactPoint.ToString()));

					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Normal %s"), *Hit.ImpactNormal.ToString()));
				}*/

				AActor* HitActor = Hit.GetActor();
				
				UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DamageType);
			}
		}
		

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != nullptr)
		{
			MeshComp->PlayAnimation(FireAnimation, false);
		}
	}
}


