#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_Slot.generated.h"

UCLASS()
class STRONGMETALSTONE_API UWC_Slot : public UWC_SMSUserWidget
{
	GENERATED_BODY()

public:
	// 마우스 버튼 누를 때
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// Drag 감지
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	// Drop 감지
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	// 슬롯 비우는 함수
	UFUNCTION(BlueprintCallable)
	virtual void ClearSlot();

	// 슬롯 갱신 함수
	UFUNCTION(BlueprintCallable)
	virtual void RefreshSlot();

protected:
	// 슬롯 이미지
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
	TSubclassOf<UWC_Slot> DragVisualClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	UTexture2D* ItemImage;
};