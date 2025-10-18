// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "WC_CommunityWidget.generated.h"

class AC_WorldPlayerController;
class AC_PlayerCharacter;
class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_CommunityWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonParty();

	UFUNCTION()
	void OnButtonFight();

	UFUNCTION()
	void OnButtonExit();

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Job;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Name;

private:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Party;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Fight;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Exit;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;

};
