// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/C_TitleHUD.h"
#include "Widget/Title/WC_TitleWidget.h"
#include "Widget/Title/Customizing/WC_FaceColorWidget.h"

void AC_TitleHUD::BeginPlay()
{
	Super::BeginPlay();

	TitleWidget = Cast<UWC_TitleWidget>(CreateWidget<UUserWidget>(GetOwningPlayerController(), WidgetClass));
	TitleWidget->AddToViewport();

	SetInputMode(EInputMode::GameAndUI,true);
}

void AC_TitleHUD::SetTitleWidgetSwitcherIndex(int _index)
{
	TitleWidget->SetWidgetSwitcherIndex(_index);
	if (_index == 3)
	{
		TitleWidget->WBPC_CustomizingWidget->HiddenButtonByJob();
		TitleWidget->WBPC_CustomizingWidget->FaceColorWidget->FaceColorSlider->SetValue(0); // 얼굴색 변경 슬라이더 초기화
	}
}

void AC_TitleHUD::SetWarningMessage(const FText& _Text)
{
	TitleWidget->SetWarningMessage(_Text);
}

void AC_TitleHUD::UpdateCharacter(AC_PlayerCharacter* Character)
{
	CustomChar = Character;
}
