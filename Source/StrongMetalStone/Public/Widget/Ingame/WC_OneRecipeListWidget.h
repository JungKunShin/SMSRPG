// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_OneRecipeListWidget.generated.h"

class UDA_RecipeData;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_OneRecipeListWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	UFUNCTION()
	void OnSlotClicked();
	
	UFUNCTION(BlueprintCallable)
	void SetSlot(UDA_RecipeData* NewRecipeData);

public:
	// 아이템 데이터
	UPROPERTY(BlueprintReadOnly)
	UDA_RecipeData* RecipeData;

	UPROPERTY(meta = (BindWidget))
	UImage* RecipeImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RecipeName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RecipeDesc;
	
};
