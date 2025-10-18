// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_ResultWidget.generated.h"

class UTextBlock;
class UWC_SMSButton;
class UWC_ResultCharacterWidget;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_ResultWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct()override;

	UFUNCTION()
	void OnBackButtonClicked();
public:
	void SetText(FString Boss);

	void SetCharacter(UWC_ResultCharacterWidget* Result);

public:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSButton* BackButton;

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* PartyInfo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_DefeatTitle;

	int32 PortNum = 6774;
};
