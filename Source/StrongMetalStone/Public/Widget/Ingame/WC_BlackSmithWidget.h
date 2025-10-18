// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_BlackSmithWidget.generated.h"

class UWC_ScriptWidget;
class UWC_SMSButton;
class UWC_ItemSlot;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_BlackSmithWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	

private:
	virtual void NativeConstruct();

	UFUNCTION()
	void OnCloseButtonClicked();

	UFUNCTION()
	void OnUpgradeButtonClicked();
public:
	UPROPERTY(meta = (BindWidget))
	UWC_ScriptWidget* ScriptWidget;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* BTN_Upgrade;

	UPROPERTY(meta = (BindWidget))
	UWC_ItemSlot* WBPC_ItemSlot;

	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* CloseButton;
};
