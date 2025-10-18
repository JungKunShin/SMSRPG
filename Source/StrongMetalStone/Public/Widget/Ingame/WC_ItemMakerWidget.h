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

	// 나가기 버튼 누르면 실행
	UFUNCTION()
	void OnCloseButtonClicked();

public:
	UFUNCTION()
	void InitRecipeScrollBox(class UDA_RecipeDataList* RecipeDataList);
public:
	UPROPERTY(meta = (BindWidget))
	UWC_ScriptWidget* ScriptWidget; //대화창

	UPROPERTY(meta = (BindWidget))
	class UWC_SMSButton* CloseButton;	// 나가기 버튼

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* RecipeScrollBox; //목록

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UWC_OneRecipeListWidget> RecipeSlotClass;
};
