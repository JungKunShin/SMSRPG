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
	// ��Ŭ�� �� Drag�� ����ϱ� ���� ��Ŭ���� ��
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		// ��Ŭ�� Ȯ�� �� ��ȯ
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UWC_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	// �̹����� ���ٸ� ��ȯ
	if (!ItemImage) return;

	// DraggedSlot�� ���ٸ� ��ȯ
	if (!DragVisualClass) return;

	// DraggedSlot Widget ����
	UWC_Slot* DragVisual = CreateWidget<UWC_Slot>(GetWorld(), DragVisualClass);
	
	// �̹��� ����
	DragVisual->ItemSlot->SetBrushFromTexture(ItemImage);

	// DragDropOperation ����
	UC_ItemDragDropOperation* DragOperation = NewObject<UC_ItemDragDropOperation>();

	// DragDropOperation ����
	DragOperation->DefaultDragVisual = DragVisual;
	DragOperation->DefaultDragVisual->SetVisibility(ESlateVisibility::HitTestInvisible);
	DragOperation->Pivot = EDragPivot::MouseDown;
	DragOperation->ItemSlot = this;
	DragOperation->ItemImage = ItemImage;

	// DragDropOperation ��ȯ
	OutOperation = DragOperation;
}

bool UWC_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UC_ItemDragDropOperation* DragOperation = Cast<UC_ItemDragDropOperation>(InOperation);
	
	// DragDropOperation, �巡�� �̹��� �� ������ ������ ��ȯ
	if (!DragOperation || !DragOperation->ItemSlot || !DragOperation->ItemImage) return false;

	// �巡���� ������ �ڽ��̸� ��ȯ
	if (DragOperation->ItemSlot == this) return false;

	// �巡���� ���԰� ���� ���� ��� �������� ��
	if (UWC_ItemSlot* DraggedItemSlot = Cast<UWC_ItemSlot>(DragOperation->ItemSlot))
	{
		if (UWC_ItemSlot* OtherSlot = Cast<UWC_ItemSlot>(this))
		{
			return OtherSlot->DropSlot(DraggedItemSlot);
		}
	}
	// �� ���� ��� ��ų�� ��
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

	// ���� ����
	ItemImage = nullptr;
	ItemSlot->SetBrushFromTexture(ItemImage);
}

void UWC_Slot::RefreshSlot()
{
	FSlateBrush EmptyBrush;

	if (!ItemImage)
	{
		// �귯�ø� �ʱ�ȭ�ϰ� �����ϰ� ����
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