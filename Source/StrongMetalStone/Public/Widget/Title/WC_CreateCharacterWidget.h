// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/Button.h"
#include "WC_CreateCharacterWidget.generated.h"

/**
 * 
 */
class AC_PlayerCharacter;
class UWC_SMSButton;

UCLASS()
class STRONGMETALSTONE_API UWC_CreateCharacterWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
private:
	const FText& ERROR_JOB = FText::FromString(TEXT("직업을 선택해주십시오."));	

	const int MAX_CHARACTER_NUM = 3;
	const int MIN_CHARACTER_NAME_NUM = 3;

private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonWarrior();

	UFUNCTION()
	void OnButtonMage();

	UFUNCTION()
	void OnButtonSelect();

	UFUNCTION()
	void OnButtonBack();
	
	void CharacterSpawn(EPlayerJob Job);

public:
	UPROPERTY()
	AC_PlayerCharacter* SpawnCharacter;

private:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Warrior;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Mage;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Select;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Back;

	EPlayerJob CurSelectJob;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSubclassOf<AC_PlayerCharacter> WarriorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSubclassOf<AC_PlayerCharacter> MageClass;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
};
