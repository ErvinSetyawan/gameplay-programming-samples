// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatsMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSCPPMOBILE_API UStatsMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHealthBarPercent(float Percent);
	void SetManaBarPercent(float Percent);
	void SetLevel(int32 Level);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ManaProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextLevel;
};
