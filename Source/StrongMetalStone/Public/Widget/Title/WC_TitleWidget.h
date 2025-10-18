// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Widget/Title/WC_LoginWidget.h"
#include "Widget/Title/WC_TitleWarningWidget.h"
#include "Widget/Title/WC_CreateCharacterWidget.h"
#include "Widget/Title/WC_CustomizingWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "WC_TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_TitleWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	

private:
	virtual void NativeConstruct() override;
public:
	void TextInit();

	void SetWidgetSwitcherIndex(int _index);
	
	void SetWarningMessage(const FText& _Text);	
public:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* TitleWidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWC_LoginWidget* WBPC_LoginWidget;

	UPROPERTY(meta = (BindWidget))
	UWC_CreateCharacterWidget* WBPC_CreateCharacterWidget;

	UPROPERTY(meta = (BindWidget))
	UWC_TitleWarningWidget* WBPC_TitleWarningWidget;

	UPROPERTY(meta = (BindWidget))
	UWC_CustomizingWidget* WBPC_CustomizingWidget;

	int PreWidgetNum = 0;
	int CurWidgetNum = 0;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* WarningSound;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Title1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Title2;
};
