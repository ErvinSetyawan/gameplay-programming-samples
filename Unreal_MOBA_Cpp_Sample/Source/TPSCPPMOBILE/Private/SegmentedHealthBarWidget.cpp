// Fill out your copyright notice in the Description page of Project Settings.


#include "SegmentedHealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Engine/Texture2D.h"

void USegmentedHealthBarWidget::SetHealth(float CurrentHealth)
{
    if (HealthProgressBar)
    {
        float DivisionSize = 1.0f / MaxDivisions;
        int32 NumDivisionsToShow = FMath::Clamp(FMath::CeilToInt(CurrentHealth / DivisionSize), 0, MaxDivisions);

        HealthProgressBar->SetPercent(CurrentHealth / MaxDivisions);

        if (DivisionTextures.IsValidIndex(NumDivisionsToShow - 1))
        {
            UTexture2D* DivisionTexture = DivisionTextures[NumDivisionsToShow - 1];
            // Set the division texture to your progress bar or desired widget
        }
    }
}
