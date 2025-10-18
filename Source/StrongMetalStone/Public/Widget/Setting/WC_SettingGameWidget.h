// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_SettingGameWidget.generated.h"

class USlider;
class UComboBoxString;

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_SettingGameWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

private:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnMouseSpeedChanged(float Value);

    UFUNCTION()
    void OnScreenSizeSelected(FString SelectedItem, ESelectInfo::Type SelectionType);

    void SaveSetting();    
private:
    //마우스 감도
    UPROPERTY(meta = (BindWidget))
    USlider* Slider_MouseSpeed;
    //화면 크기
    UPROPERTY(meta = (BindWidget))
    UComboBoxString* ComboBoxScreenSize;

	

public:
    FVector2D SelectedScreenSize = FVector2D(1920,1080);

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundBase* BeginSound;
};
