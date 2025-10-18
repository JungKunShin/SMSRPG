// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_ItemMakerWidget.generated.h"

class UWC_ScriptWidget;
class UWC_OneRecipeListWidget;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UWC_ItemMakerWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct();

	// ������ ��ư ������ ����
	UFUNCTION()
	void OnCloseButtonClicked();

public:
	UFUNCTION()
	void InitRecipeScrollBox(class UDA_RecipeDataList* RecipeDataList);
public:
	UPROPERTY(meta = (BindWidget))
	UWC_ScriptWidget* ScriptWidget; //��ȭâ

	UPROPERTY(meta = (BindWidget))
	class UWC_SMSButton* CloseButton;	// ������ ��ư

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* RecipeScrollBox; //���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UWC_OneRecipeListWidget> RecipeSlotClass;
};
