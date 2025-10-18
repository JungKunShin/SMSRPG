// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_OneRecipeListWidget.h"
#include "Data/Recipe/DA_RecipeData.h"
#include "Data/DA_ItemData.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"


FReply UWC_OneRecipeListWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// 구매 확인창 띄우기
		OnSlotClicked();
		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UWC_OneRecipeListWidget::OnSlotClicked()
{
}

void UWC_OneRecipeListWidget::SetSlot(UDA_RecipeData* NewRecipeData)
{
	// 아이템 데이터 및 수량 설정
	RecipeData = NewRecipeData;

	// 아이템 이미지 설정
	if (RecipeData)
	{
		
		RecipeImage->SetBrushFromTexture(Cast<UDA_ItemData>(RecipeData->ResultClass->GetDefaultObject())->Icon);

		RecipeName->SetText(FText::FromName(Cast<UDA_ItemData>(RecipeData->ResultClass->GetDefaultObject())->ItemData.Name));
		RecipeDesc->SetText(Cast<UDA_ItemData>(RecipeData->ResultClass->GetDefaultObject())->ItemData.Description);
	}
}
