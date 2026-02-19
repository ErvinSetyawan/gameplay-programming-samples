// Fill out your copyright notice in the Description page of Project Settings.


#include "TESWIDGET.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Main.h"
#include "GMTesNew.h"

void UTESWIDGET::NativeConstruct()
{
	if(TextBtn)
	{
		TextBtn->OnClicked.AddDynamic(this, &UTESWIDGET::TextBtnOnClick);
	}
}

void UTESWIDGET::TextBtnOnClick()
{
	//TextLabel->SetText(FText::AsNumber(17));

	AMain* Main = Cast<AMain>(GetOwningPlayerPawn());
	Main->ComboInput(); // Call play anim montage
	/*Main->TimelineProgress(10);
	Main->CurveTimeline.PlayFromStart();*/
}
