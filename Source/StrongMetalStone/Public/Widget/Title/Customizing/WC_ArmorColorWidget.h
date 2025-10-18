// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_ArmorColorWidget.generated.h"

class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_ArmorColorWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnGrassHopherButtonClicked();
	UFUNCTION()
	void OnOriginalButtonClicked();
	UFUNCTION()
	void OnIronManButtonClicked();
	UFUNCTION()
	void OnDarkKnightButtonClicked();
	UFUNCTION()
	void OnDoraemonButtonClicked();
	UFUNCTION()
	void OnDVaButtonClicked();

	void BasicChest(FLinearColor Armor, FLinearColor Neck, FLinearColor Detail);
	void BasicBelly(FLinearColor Armor, FLinearColor Biceps, FLinearColor FormArm, FLinearColor Detail);
	void BasicSkirt(FLinearColor Armor, FLinearColor DetailUp, FLinearColor DetailDown, FLinearColor Point, FLinearColor Thigh);
	void BasicKnee(FLinearColor Armor, FLinearColor Leather, FLinearColor Detail);

	void OnButtonSound();

public:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* GrassHopherButton;
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* OriginalButton;
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* IronManButton;
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* DarkKnightButton;
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* DoraemonButton;
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* DVaButton;

	AC_PlayerCharacter* CustomCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
	
};
