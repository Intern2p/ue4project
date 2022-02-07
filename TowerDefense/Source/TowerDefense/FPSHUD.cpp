// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHUD.h"
#include "Components/WidgetComponent.h"

void AFPSHUD::BeginPlay()
{
    Super::BeginPlay();

    // If any widgets need to be added
    if (AllUIWidgets.Num() > 0)
    {
        // Iterate through all widgets
        for (TSubclassOf<UUserWidget> widget : AllUIWidgets)
        {
            // Create an instance of the widget and add to viewport
            UUserWidget* createdWidget = CreateWidget<UUserWidget>(GetWorld(), widget);
            createdWidget->AddToViewport();
        }
    }
}

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();

    if (CrosshairTexture)
    {
        // Find the center of our canvas.
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

        // Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // Draw the crosshair at the centerpoint.
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
       // Canvas->DrawItem(TileItem);

        //DrawTexture(CrosshairTexture, Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f, 192.f, 192.f, 0.f, 0.f, 1.f, 1.f, FLinearColor::Black);
        DrawRect(FColor::White, Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f, 2.f, 2.f);
       // DrawCircle(GetWorld(), GetOwner()->GetActorLocation(), XVector, YVector, DebugLineColor, GetPolarGridElement(i, j, k).X, 100, false, -1.0f, LineDepthInt8, LineThickness);
    }
}

void AFPSHUD::ShowGameOverWidget()
{
    UUserWidget* createdWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidget);
    createdWidget->AddToViewport();
}

void AFPSHUD::ShowStageWaveWidget()
{
    if (NumStageWidget)
    { 
        if (!WidgetStageWave)
            WidgetStageWave = CreateWidget<UUserWidget>(GetWorld(), NumStageWidget);
        WidgetStageWave->AddToViewport();

        GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPSHUD::HideStageWaveWidget, 2, false);
    }
}

void AFPSHUD::HideStageWaveWidget()
{
    WidgetStageWave->RemoveFromViewport();
}