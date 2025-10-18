// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/Slider.h"
#include "WC_SettingSoundWidget.generated.h"

/**
 * 
 */
class UComboBoxString;

UCLASS()
class STRONGMETALSTONE_API UWC_SettingSoundWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnBGMSelected(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnMasterVolumeChanged(float NewValue);

	UFUNCTION()
	void OnBGMVolumeChanged(float NewValue);

	UFUNCTION()
	void OnEffectVolumeChanged(float NewValue);

	UFUNCTION()
	void OnUIVolumeChanged(float NewValue);
private:

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ComboBox_BGM;

	UPROPERTY(meta = (BindWidget))
	USlider* AudioVolumeSlider_Master;
	
	UPROPERTY(meta = (BindWidget))
	USlider* AudioVolumeSlider_BackGround;

	UPROPERTY(meta = (BindWidget))
	USlider* AudioVolumeSlider_Effect;

	UPROPERTY(meta = (BindWidget))
	USlider* AudioVolumeSlider_UI;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
};
