// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_ResultCharacterWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;

UCLASS()
class STRONGMETALSTONE_API UWC_ResultCharacterWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateText(FString nickName, unsigned int Damage,unsigned int Level);

	UFUNCTION()
	void UpdateImage(EPlayerJob Job);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_NickName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_Level;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TEXT_AllDamageAmount;

	UPROPERTY(meta = (BindWidget))
	UImage* Image_Job;
};
