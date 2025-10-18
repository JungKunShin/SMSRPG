// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_QuestingTextWidget.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class STRONGMETALSTONE_API UWC_QuestingTextWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateText(AC_SMSQuest* Quest);

public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TEXT_QuestCondition;
};
