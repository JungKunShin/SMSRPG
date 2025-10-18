// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_WeightSizeWidget.h"
#include "HUD/C_TitleHUD.h"
#include "Character/C_Warrior.h"
#include "Components/SkeletalMeshComponent.h"

void UWC_WeightSizeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WeightSizeSlider->OnValueChanged.AddDynamic(this, &UWC_WeightSizeWidget::OnSliderValueChanged);
}

void UWC_WeightSizeWidget::OnSliderValueChanged(float Value)
{
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		Warrior->GetMesh()->SetWorldScale3D(FVector(Value, Value, 1.0f));
	}
}
