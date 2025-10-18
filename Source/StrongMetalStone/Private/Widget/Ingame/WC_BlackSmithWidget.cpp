// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_BlackSmithWidget.h"
#include "Widget/Ingame/WC_ScriptWidget.h"
#include "Widget/Inventory/WC_ItemSlot.h"
#include "Data/DA_ItemData.h"
#include "HUD/C_WorldHUD.h"
#include "Widget/Inventory/WC_ItemSlot.h"
#include "Widget/WC_SMSButton.h"

void UWC_BlackSmithWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ScriptWidget->SetTextName(TEXT("뚝딱이"));
	ScriptWidget->SetTextScript(TEXT("HeLLo"));

	// 창 닫기 버튼 초기화
	CloseButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/Delete")), FVector3f(1.f, 1.f, 1.f));
	// 창 닫기 버튼에 함수 바인딩
	CloseButton->OnButtonClicked.AddDynamic(this, &UWC_BlackSmithWidget::OnCloseButtonClicked);

	BTN_Upgrade->Init(FText::FromString(TEXT("강화하기")), 48);
	BTN_Upgrade->OnButtonClicked.AddDynamic(this, &UWC_BlackSmithWidget::OnUpgradeButtonClicked);

	WBPC_ItemSlot->RefreshSlot();
}

void UWC_BlackSmithWidget::OnCloseButtonClicked()
{
	if (AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		WorldHUD->SetBlackSmithWidgetVisible(false);
	}
}

void UWC_BlackSmithWidget::OnUpgradeButtonClicked()
{
	if (WBPC_ItemSlot->SlotData.ItemData)
		WBPC_ItemSlot->SlotData.Grade++;
}
