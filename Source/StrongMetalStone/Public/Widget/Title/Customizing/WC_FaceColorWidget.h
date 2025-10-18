// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/Slider.h"
#include "WC_FaceColorWidget.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_FaceColorWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnSliderValueChanged(float Value);

public:
	UPROPERTY(meta = (BindWidget))
	USlider* FaceColorSlider;

	AC_PlayerCharacter* CustomCharacter;
};
