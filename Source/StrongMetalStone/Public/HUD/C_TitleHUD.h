// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUD/C_SMSHUD.h"
#include "Components/WidgetSwitcher.h"
#include "C_TitleHUD.generated.h"

class UWC_TitleWidget;

UCLASS()
class STRONGMETALSTONE_API AC_TitleHUD : public AC_SMSHUD
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

public:
	void SetTitleWidgetSwitcherIndex(int _index);
	void SetWarningMessage(const FText& _Text);
	void UpdateCharacter(AC_PlayerCharacter* Character);
public:
	UPROPERTY(BlueprintReadWrite)
	UWC_TitleWidget* TitleWidget;

	UPROPERTY(BlueprintReadWrite)
	UWidgetSwitcher* TitleWidgetSwitcher;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> WidgetClass;

	AC_PlayerCharacter* CustomChar;



};
