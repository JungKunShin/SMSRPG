// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/Button.h"
#include "WC_SelectCharacterWidget.generated.h"

class AC_PlayerCharacter;
class UWC_SMSButton;

UCLASS()
class STRONGMETALSTONE_API UWC_SelectCharacterWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
private:
	const FText& ERROR_SELECT_CHARACTER = FText::FromString(TEXT("캐릭터를 선택해주십시오."));
private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonStart();

	UFUNCTION()
	void OnButtonEnd();

	UFUNCTION()
	void OnButtonCreateCharacter();

	UFUNCTION()
	void OnButtonDeleteCharacter();
	
	void OnButtonSound();
private:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Start;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_End;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_CreateCharacter;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_DeleteCharacter;

private:

	int32 LevelPort = 6774;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
};
