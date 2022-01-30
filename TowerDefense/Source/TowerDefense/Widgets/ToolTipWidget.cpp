// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolTipWidget.h"
#include "Components/TextBlock.h"

void UToolTipWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!ToolTipText.IsEmpty())
	{
		FNumberFormattingOptions Opts;
		Opts.SetMaximumFractionalDigits(0);
		ToolTipLabel->SetText(FText::AsCultureInvariant(ToolTipText));
	}
}