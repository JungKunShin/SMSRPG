// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_ItemMakerWidget.h"
#include "Widget/Ingame/WC_ScriptWidget.h"
#include "Widget/Ingame/WC_OneRecipeListWidget.h"
#include "Widget/WC_SMSButton.h"

#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/ScrollBox.h"

#include "Data/Recipe/DA_RecipeDataList.h"

#include "HUD/C_WorldHUD.h"

void UWC_ItemMakerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ScriptWidget->SetTextName(TEXT("만들이"));
	ScriptWidget->SetTextScript(TEXT("재료만 주면 다 만들어 드립니다"));

	// 창 닫기 버튼 초기화
	CloseButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/Delete")), FVector3f(1.f, 1.f, 1.f));
	// 창 닫기 버튼에 함수 바인딩
	CloseButton->OnButtonClicked.AddDynamic(this, &UWC_ItemMakerWidget::OnCloseButtonClicked);
}

void UWC_ItemMakerWidget::OnCloseButtonClicked()
{
	if (AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		WorldHUD->SetInventoryWidgetVisible(false);
		WorldHUD->SetItemMakerWidgetVisible(false);
	}
}

void UWC_ItemMakerWidget::InitRecipeScrollBox(UDA_RecipeDataList* RecipeDataList)
{
	RecipeScrollBox->ClearChildren();
	
	int32 TotalItems = RecipeDataList->RecipeList.Num();						// 전체 아이템 개수	
	for (int32 i = 0; i < TotalItems; ++i)
	{
		// 가로 박스 생성
		UHorizontalBox* RowBox = NewObject<UHorizontalBox>(this, UHorizontalBox::StaticClass());

		// 현재 위치가 전체 아이템보다 큰 경우
		if (i >= TotalItems) break;

		UWC_OneRecipeListWidget* Slots = CreateWidget<UWC_OneRecipeListWidget>(this, RecipeSlotClass);
		Slots->SetVisibility(ESlateVisibility::Visible);		
		Slots->SetSlot(RecipeDataList->RecipeList[i]);
		
		UHorizontalBoxSlot* SlotContainer = RowBox->AddChildToHorizontalBox(Slots);
		SlotContainer->SetPadding(FMargin(4));	// 여백 설정
		

		RecipeScrollBox->AddChild(RowBox);
	}
}
