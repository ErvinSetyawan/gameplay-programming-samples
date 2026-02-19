// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TESWIDGET.generated.h"

/**
 * 
 */
UCLASS()
class TPSCPPMOBILE_API UTESWIDGET : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TextLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* TextBtn;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void TextBtnOnClick();
};
