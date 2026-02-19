// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsMainWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UStatsMainWidget::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void UStatsMainWidget::SetManaBarPercent(float Percent)
{
	if (ManaProgressBar)
	{
		ManaProgressBar->SetPercent(Percent);
	}
}

void UStatsMainWidget::SetLevel(int32 Level)
{
	if (TextLevel)
	{
		FString String = FString::Printf(TEXT("%d"), Level);
		FText Text = FText::FromString(String);
		TextLevel->SetText(Text);
	}
}
