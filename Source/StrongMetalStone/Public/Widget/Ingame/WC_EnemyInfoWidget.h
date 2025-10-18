// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Components/TextBlock.h"
#include "WC_EnemyInfoWidget.generated.h"


class UWC_SMSProgressBar;
class AC_SMSCharacter;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_EnemyInfoWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
public:	
	void OnTarget(AC_SMSCharacter* Character);
	void OffTarget();

private:
	void NativeConstruct()override;
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock_Name;
	
	FText Name;
	float Hp;
	float Groggy;
private:
	UPROPERTY(meta = (BindWidget))
	UWC_SMSProgressBar* WBPC_SMSProgressBar_Hp;
	UPROPERTY(meta = (BindWidget))
	UWC_SMSProgressBar* WBPC_SMSProgressBar_Groggy;

	FLinearColor HpColor = FLinearColor::Red;
	FLinearColor GroggyColor = FLinearColor::Yellow;
};
