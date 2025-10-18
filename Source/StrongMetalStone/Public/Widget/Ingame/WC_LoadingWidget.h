// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_LoadingWidget.generated.h"

/**
 * 
 */

UCLASS()
class STRONGMETALSTONE_API UWC_LoadingWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
private:
	const float TOTAL_TIME = 5.f;

public:
	virtual void NativeConstruct()override;

	void RandomTip();

	void UpdateProgressBar();

	void DelayUpdate();

public:
	void Init(bool OnDungeon);

private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Loading;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TEXT_Tip;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* LoadingProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Field;

	UPROPERTY(meta = (BindWidget))
	class UImage* Image_Dungeon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TEXT_Field;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TEXT_Dungeon;

	float CurTime = 0;

private:
	FTimerHandle LoadingTH;
};
