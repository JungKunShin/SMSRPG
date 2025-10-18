// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Party/WC_OnePartyWidget.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

UWC_OnePartyWidget::UWC_OnePartyWidget()
{

}

void UWC_OnePartyWidget::NativeConstruct()
{
	WBPC_SMSProgressBar_HP->SetType(EProgressBarType::HEALTH);
	WBPC_SMSProgressBar_HP->Init(1.0f, FLinearColor::Red);
}

void UWC_OnePartyWidget::SetWidget()
{
	TextBlock_NickName->SetText(FText::FromString(NickName));
}

void UWC_OnePartyWidget::HpBarUpdate(float percent)
{
	WBPC_SMSProgressBar_HP->Update(percent);
}
