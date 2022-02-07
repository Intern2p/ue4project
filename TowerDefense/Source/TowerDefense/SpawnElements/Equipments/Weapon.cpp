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
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
		
	if (MyOwner)
	{
		ABaseCharacter* MyCharacter = Cast<ABaseCharacter>(MyOwner);
		if (MyCharacter)
		{
			FVector EyeLocation;
			FRotator EyeRotation;
			MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
			EyeRotation = MyCharacter->FollowCamera->GetComponentRotation();

			FVector ShotDirection = EyeRotation.Vector();

			float HalfRad = FMath::DegreesToRadians(BulletSpread);

			ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);
			FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(MyOwner);
			QueryParams.AddIgnoredActor(this);
			QueryParams.bTraceComplex = true;
			QueryParams.bReturnPhysicalMaterial = true;

			EPhysicalSurface SurfaceType = SurfaceType_Default;
			FHitResult Hit;
			//DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Green, true);
			if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
			{
				if (Hit.bBlockingHit)
				{
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
}


