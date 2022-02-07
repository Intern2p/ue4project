// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUIWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "TowerDefense/Components/InventoryComponent.h"
#include "TowerDefense/Characters/DefenderCharacter.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Wood.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Stone.h"
#include "TowerDefense/SpawnElements/CraftingMaterials/Metal.h"
#include "TowerDefense/TowerDefender_GameMode.h"
#include "TowerDefense/TargetLocation.h"

void UPlayerUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ADefenderCharacter* Char = Cast<ADefenderCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Char)
		OwnerCharacter = Char;

	TArray<AActor*> FoundTarget;
	TSubclassOf<ATargetLocation> classNameLocation = ATargetLocation::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classNameLocation, FoundTarget);
	for (AActor* TActor : FoundTarget)
	{
		TargetLocation = Cast<ATargetLocation>(TActor);
	}

	isActiveToolTip = true;
	VisibleToolTip = ESlateVisibility::Hidden;
	VisibleShowMessage = ESlateVisibility::Hidden;
	VisibleDestructionBox = ESlateVisibility::Hidden;
}

void UPlayerUIWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (OwnerCharacter)
	{
		FNumberFormattingOptions Opts;
		Opts.SetMaximumFractionalDigits(0);

		/* Health */
		if (OwnerCharacter->Health)
		{
			HealthBar->SetPercent(OwnerCharacter->GetHealth() / OwnerCharacter->GetMaxHealth());
			CurrentHealthLabel->SetText(FText::AsNumber(OwnerCharacter->GetHealth(), &Opts));
			MaxHealthLabel->SetText(FText::AsNumber(OwnerCharacter->GetMaxHealth(), &Opts));
		}

		/*Inventory*/
		if (OwnerCharacter->Inventory)
		{
			CountWoodLabel->SetText(FText::AsNumber(OwnerCharacter->Inventory->GetCountMaterial(AWood::StaticClass()->GetName()), &Opts));
			CountStoneLabel->SetText(FText::AsNumber(OwnerCharacter->Inventory->GetCountMaterial(AStone::StaticClass()->GetName()), &Opts));
			CountMetalLabel->SetText(FText::AsNumber(OwnerCharacter->Inventory->GetCountMaterial(AMetal::StaticClass()->GetName()), &Opts));
		}

		/*Armor*/
		if (OwnerCharacter->ArmorClass)
		{
			TypeArmorLabel->SetText(FText::FromString(OwnerCharacter->GetArmorMaterial()));
		}
		else
		{
			TypeArmorLabel->SetText(FText::FromString(TEXT("Default")));
		}
		BlockDamageLabel->SetText(FText::AsNumber(OwnerCharacter->GetArmorBlockingDamage(), &Opts));

		/*ToolTip*/
		if (OwnerCharacter->ToolTip == "")
		{
			VisibleToolTip = ESlateVisibility::Hidden;
		}
		else
		{
			VisibleToolTip = ESlateVisibility::Visible;
			ToolTipLabel->SetText(FText::FromString(OwnerCharacter->ToolTip));
		}
		

		/*ShowMessage*/
		if (OwnerCharacter->ShowMessage == "")
		{
			VisibleShowMessage = ESlateVisibility::Hidden;
		}
		else
		{
			VisibleShowMessage = ESlateVisibility::Visible;
			ShowMessageLabel->SetText(FText::FromString(OwnerCharacter->ShowMessage));
		}

		/*Destruction*/
		if (TargetLocation->isDestruct)
		{
			VisibleDestructionBox = ESlateVisibility::Visible;
			DestructionBar->SetPercent(TargetLocation->PercentDestruction/100.f);
			DestructionValue->SetText(FText::AsNumber(TargetLocation->PercentDestruction, &Opts));
		}
		else
		{
			VisibleDestructionBox = ESlateVisibility::Hidden;
		}
	}
}
