// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_MgClothColorWidget.generated.h"

class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_MgClothColorWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnOriginalButtonClicked();

	UFUNCTION()
	void OnGrassHopherButtonClicked();
	UFUNCTION()
	void OnGodLaButtonClicked();
	UFUNCTION()
	void OnAphroditeButtonClicked();
	UFUNCTION()
	void OnPoopGuyButtonClicked();
	UFUNCTION()
	void OnBonoBonoButtonClicked();

	void OnButtonSound();

public:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* OriginalButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* GrassHopherButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* GodLaButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* AphroditeButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* PoopGuyButton;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* BonoBonoButton;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;

};
