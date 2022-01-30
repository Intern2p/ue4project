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

void UPlayerUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ADefenderCharacter* Char = Cast<ADefenderCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Char)
	{
		OwnerCharacter = Char;
	}
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("AddDynamic")));
	Char->ChangeStateElement.AddDynamic(this, &UPlayerUIWidget::ChangeInventory);
	VisibleToolTip = ESlateVisibility::Hidden;
	isActiveToolTip = false;
}

//FText UPlayerUIWidget::SetToolTip()
//{
//	UWorld* World = GetWorld();
//	if (World)
//	{
//		ATowerDefender_GameMode* GameMode = Cast<ATowerDefender_GameMode>(World->GetAuthGameMode());
//		if (GameMode)
//		{
//			return FText::FromString(GameMode->ToolTipText);
//		}
//	}
//	return FText();
//}

void UPlayerUIWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (OwnerCharacter)
	{
		HealthBar->SetPercent(OwnerCharacter->GetHealth() / OwnerCharacter->GetMaxHealth());
		FNumberFormattingOptions Opts;
		Opts.SetMaximumFractionalDigits(0);
		CurrentHealthLabel->SetText(FText::AsNumber(OwnerCharacter->GetHealth(), &Opts));
		MaxHealthLabel->SetText(FText::AsNumber(OwnerCharacter->GetMaxHealth(), &Opts));
		if (OwnerCharacter->Inventory)
		{
			CountWoodLabel->SetText(FText::AsNumber(OwnerCharacter->Inventory->GetCountMaterial(AWood::StaticClass()->GetName()), &Opts));
			CountStoneLabel->SetText(FText::AsNumber(OwnerCharacter->Inventory->GetCountMaterial(AStone::StaticClass()->GetName()), &Opts));
			CountMetalLabel->SetText(FText::AsNumber(OwnerCharacter->Inventory->GetCountMaterial(AMetal::StaticClass()->GetName()), &Opts));
		}

		if (OwnerCharacter->ArmorClass && OwnerCharacter->GetArmorMaterial())
		{
			TypeArmorLabel->SetText(FText::FromString(OwnerCharacter->GetArmorMaterial()->GetClass()->GetName()));
		}
		else
		{
			TypeArmorLabel->SetText(FText::FromString(TEXT("Default")));
		}
		BlockDamageLabel->SetText(FText::AsNumber(OwnerCharacter->GetArmorBlockingDamage(), &Opts));
	}
}

void UPlayerUIWidget::ChangeInventory(FString TextToolTip)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("teeeeeeeese")));
		ToolTipLabel->SetText(FText::FromString(TextToolTip));
		isActiveToolTip = true;
		VisibleToolTip = ESlateVisibility::Visible;
}