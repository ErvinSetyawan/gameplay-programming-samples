// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetStatsHero.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class TPSCPPMOBILE_API UWidgetStatsHero : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HPDamageProgressBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HPProgressBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* ManaProgressBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextLevel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TextPlayerName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UHorizontalBox* SegmentsHorizonBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HPVar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MaxHPVar;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* LevelProgressimg;

	/*UFUNCTION()
	void AddSlotSegments();*/

};
