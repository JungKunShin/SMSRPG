// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_DeathWidget.h"
#include "Character/C_PlayerCharacter.h"
#include "HUD/C_WorldHUD.h"
#include "Widget/WC_SMSButton.h"

void UWC_DeathWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 부활
	if (WBPC_SMSButton_Revive)
	{
		// 버튼 초기화
		WBPC_SMSButton_Revive->Init(FText::FromString(TEXT("부활하기")), 20);

		// 함수 이벤트 바인딩
		WBPC_SMSButton_Revive->OnButtonClicked.AddDynamic(this, &UWC_DeathWidget::OnReviveButtonClicked);
	}
}

void UWC_DeathWidget::OnReviveButtonClicked()
{
	CastWCharacter(GetMyCharacter())->Init();
	SetVisibility(ESlateVisibility::Hidden);

	CastWHUD(GetMyHUD())->SetMouseMode(false);
}

