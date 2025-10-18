// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "WC_TitleWarningWidget.generated.h"


class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_TitleWarningWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

public:
	void SetWarningMessage(const FText& _Text);

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButton_Back();



private:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Back;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Warning;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
};
