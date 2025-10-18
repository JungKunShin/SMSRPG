// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "WC_SettingWidget.generated.h"

class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_SettingWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void OnCloseButtonClicked();

	UFUNCTION()
	void OnGameButtonClicked();
	
	UFUNCTION()
	void OnSoundButtonClicked();
	
	UFUNCTION()
	void OnSaveButtonClicked();
public:
	UPROPERTY(meta = (BindWidget))
	class UWC_SMSButton* WBPC_SMSButton_Close;	// ������ ��ư

	UPROPERTY(meta = (BindWidget))
	class UWC_SMSButton* WBPC_SMSButton_Game;	// ���� ��ư

	UPROPERTY(meta = (BindWidget))
	class UWC_SMSButton* WBPC_SMSButton_Sound;	// ���� ��ư

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher_Setting;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
};
