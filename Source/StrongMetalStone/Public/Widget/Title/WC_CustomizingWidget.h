// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "WC_CustomizingWidget.generated.h"

class UWC_SMSButton;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_CustomizingWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
private:	
	const FText ERROR_NICKNAME_INPUT = FText::FromString(TEXT("중복 닉네임 입니다."));
	const FText ERROR_NICKNAME_NUM = FText::FromString(TEXT("닉네임을 한글자 이상 입력해주세요"));
	const int MAX_NAME_NUM = 8;
	const int MIN_NAME_NUM = 1;
private:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnButtonClickEnter();

	UFUNCTION()
	void OnButtonClickBack();


	UFUNCTION()
	void OnTextChangedCharacterName(const FText& NewText);

	UFUNCTION()
	void OnTextCommittedCharacterName(const FText& Text, ETextCommit::Type CommitType);

	UFUNCTION()
	void OnFaceColorButtonClicked();

	UFUNCTION()
	void OnEyeColorButtonClicked();

	UFUNCTION()
	void OnHairColorButtonClicked();

	UFUNCTION()
	void OnWeaponColorButtonClicked();

	UFUNCTION()
	void OnEyeLashColorButtonClicked();

	//UFUNCTION()
	//void OnWeightSizeButtonClicked();

	UFUNCTION()
	void OnArmorColorButtonClicked();

	UFUNCTION()
	void OnMgClothColorButtonClicked();

	UFUNCTION()
	void OnMgBagColorButtonClicked();

	void InitButton();

	void OnButtonSound();

public:
	void HiddenButtonByJob();

public:

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableText_CharacterName;
private:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Select;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_Back;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_FaceColor;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_EyeColor;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_HairColor;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_WeaponColor;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_EyeLashColor;

	//UPROPERTY(meta = (BindWidget))
	//UWC_SMSButton* Button_WeightSize;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_ArmorColor;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_MgClothColor;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* Button_MgBagColor;

public:
	UPROPERTY(meta = (BindWidget))
	class UWC_FaceColorWidget* FaceColorWidget;

	UPROPERTY(meta = (BindWidget))
	class UWC_EyeColorWidget* EyeColorWidget;

	UPROPERTY(meta = (BindWidget))
	class UWC_HairColorWidget* HairColorWidget;

	UPROPERTY(meta = (BindWidget))
	class UWC_WeaponColorWidget* WeaponColorWidget;

	UPROPERTY(meta = (BindWidget))
	class UWC_EyeLashColorWidget* EyeLashColorWidget;

	//UPROPERTY(meta = (BindWidget))
	//class UWC_WeightSizeWidget* WeightSizeWidget;

	UPROPERTY(meta = (BindWidget))
	class UWC_ArmorColorWidget* ArmorColorWidget;

	UPROPERTY(meta = (BindWidget))
	class UWC_MgClothColorWidget* MgClothColorWidget;

	UPROPERTY(meta = (BindWidget))
	class UWC_MgBagColorWidget* MgBagColorWidget;

	FString InputName;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ButtonSound;
};
