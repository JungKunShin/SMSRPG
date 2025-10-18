// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_HairColorWidget.generated.h"

class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_HairColorWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnRedButtonClicked();
	UFUNCTION()
	void OnGreenButtonClicked();
	UFUNCTION()
	void OnBlueButtonClicked();
	UFUNCTION()
	void OnBlackButtonClicked();
	UFUNCTION()
	void OnOriginalButtonClicked();
	UFUNCTION()
	void OnYellowButtonClicked();
	UFUNCTION()
	void OnCyanButtonClicked();
	UFUNCTION()
	void OnMagentaButtonClicked();

	void OnButtonSound();

public:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* RedButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* GreenButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* BlueButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* BlackButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* OriginalButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* YellowButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* CyanButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* MagentaButton;

	AC_PlayerCharacter* CustomCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
	
};
