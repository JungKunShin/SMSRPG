// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_WeaponColorWidget.generated.h"

class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_WeaponColorWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnRedButtonClicked();
	UFUNCTION()
	void OnGreenButtonClicked();
	UFUNCTION()
	void OnOriginalButtonClicked();

	void OnButtonSound();

public:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* RedButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* GreenButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* OriginalButton;

	AC_PlayerCharacter* CustomCharacter;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
	
};
