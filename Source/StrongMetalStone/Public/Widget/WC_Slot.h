#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_Slot.generated.h"

UCLASS()
class STRONGMETALSTONE_API UWC_Slot : public UWC_SMSUserWidget
{
	GENERATED_BODY()

public:
	// ���콺 ��ư ���� ��
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// Drag ����
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	// Drop ����
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
	virtual void ClearSlot();

	// ���� ���� �Լ�
	UFUNCTION(BlueprintCallable)
	virtual void RefreshSlot();

protected:
	// ���� �̹���
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
	TSubclassOf<UWC_Slot> DragVisualClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UTexture2D* ItemImage;
};