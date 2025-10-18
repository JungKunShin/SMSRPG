// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_FaceColorWidget.h"
#include "HUD/C_TitleHUD.h"
#include "Character/C_PlayerCharacter.h"

void UWC_FaceColorWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FaceColorSlider->OnValueChanged.AddDynamic(this, &UWC_FaceColorWidget::OnSliderValueChanged);
}

void UWC_FaceColorWidget::OnSliderValueChanged(float Value)
{
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(CustomCharacter);
	if (Character)
	{
		CustomCharacter->NewColor(Value);
		CustomCharacter->CharacterInfo.CustomizingInfo.FaceColorNum = Value;
	}
}
