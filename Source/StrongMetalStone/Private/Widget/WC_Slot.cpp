#include "Widget/WC_Slot.h"
#include "Widget/Inventory/C_ItemDragDropOperation.h"
#include "Widget/Inventory/WC_ItemSlot.h"
#include "Widget/Ingame/WC_SkillSlot.h"

#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "Components/Image.h"
#include "Engine/Texture2D.h"

FReply UWC_Slot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// 좌클릭 시 Drag를 허용하기 위해 좌클릭일 때
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		// 좌클릭 확인 후 반환
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UWC_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	// 이미지가 없다면 반환
	if (!ItemImage) return;

	// DraggedSlot이 없다면 반환
	if (!DragVisualClass) return;

	// DraggedSlot Widget 생성
	UWC_Slot* DragVisual = CreateWidget<UWC_Slot>(GetWorld(), DragVisualClass);
	
	// 이미지 설정
	DragVisual->ItemSlot->SetBrushFromTexture(ItemImage);

	// DragDropOperation 생성
	UC_ItemDragDropOperation* DragOperation = NewObject<UC_ItemDragDropOperation>();

	// DragDropOperation 설정
	DragOperation->DefaultDragVisual = DragVisual;
	DragOperation->DefaultDragVisual->SetVisibility(ESlateVisibility::HitTestInvisible);
	DragOperation->Pivot = EDragPivot::MouseDown;
	DragOperation->ItemSlot = this;
	DragOperation->ItemImage = ItemImage;

	// DragDropOperation 반환
	OutOperation = DragOperation;
}

bool UWC_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UC_ItemDragDropOperation* DragOperation = Cast<UC_ItemDragDropOperation>(InOperation);
	
	// DragDropOperation, 드래그 이미지 및 슬롯이 없으면 반환
	if (!DragOperation || !DragOperation->ItemSlot || !DragOperation->ItemImage) return false;

	// 드래그한 슬롯이 자신이면 반환
	if (DragOperation->ItemSlot == this) return false;

	// 드래그한 슬롯과 놓일 슬롯 모두 아이템일 때
	if (UWC_ItemSlot* DraggedItemSlot = Cast<UWC_ItemSlot>(DragOperation->ItemSlot))
	{
		if (UWC_ItemSlot* OtherSlot = Cast<UWC_ItemSlot>(this))
		{
			return OtherSlot->DropSlot(DraggedItemSlot);
		}
	}
	// 두 슬롯 모두 스킬일 때
	else if (UWC_SkillSlot* DraggedSkillSlot = Cast<UWC_SkillSlot>(DragOperation->ItemSlot))
	{
		if (UWC_SkillSlot* OtherSlot = Cast<UWC_SkillSlot>(this))
		{
			return OtherSlot->DropSlot(DraggedSkillSlot);
		}
	}

	return true;
}

void UWC_Slot::ClearSlot()
{
	if (!ItemSlot) return;

	// 슬롯 비우기
	ItemImage = nullptr;
	ItemSlot->SetBrushFromTexture(ItemImage);
}

void UWC_Slot::RefreshSlot()
{
	FSlateBrush EmptyBrush;

	if (!ItemImage)
	{
		// 브러시를 초기화하고 투명하게 설정
		EmptyBrush.TintColor = FSlateColor(FLinearColor::Transparent);
		ItemSlot->SetBrush(EmptyBrush);
	}
	else
	{
		EmptyBrush.TintColor = FSlateColor(FLinearColor::White);
		ItemSlot->SetBrush(EmptyBrush);
		ItemSlot->SetBrushFromTexture(ItemImage);
	}
}