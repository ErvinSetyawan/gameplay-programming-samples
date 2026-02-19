// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SegmentedHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSCPPMOBILE_API USegmentedHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UProgressBar* HealthProgressBar;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
    int32 MaxDivisions;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
    TArray<UTexture2D*> DivisionTextures;

public:
    UFUNCTION(BlueprintCallable)
    void SetHealth(float CurrentHealth);
};
