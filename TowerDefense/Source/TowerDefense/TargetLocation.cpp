// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetLocation.h"

ATargetLocation::ATargetLocation()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT(" Create TargetLocation")));
}