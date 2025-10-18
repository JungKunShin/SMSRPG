// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "WC_InvitePartyWidget.generated.h"

class AC_PlayerCharacter;
class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_InvitePartyWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonYes();

	UFUNCTION()
	void OnButtonNo();

	void InviteParty();
private:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Yes;
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_No;

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_PartyOwner;

	AC_PlayerCharacter* Inviter;

	FTimerHandle DelayTimerHandle;

private:
	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* BeginSound;
};
