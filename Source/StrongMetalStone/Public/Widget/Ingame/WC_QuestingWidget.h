// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/WC_SMSUserWidget.h"
#include "WC_QuestingWidget.generated.h"

/**
 * 
 */
class UWC_SMSButton;

UCLASS()
class STRONGMETALSTONE_API UWC_QuestingWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct()override;

public:
	UFUNCTION()
	void OnOffButtonClicked();

	UFUNCTION()
	void SetQuest(UWC_QuestingTextWidget* QuestText);

	UFUNCTION()
	void RemoveQuest(int32 Index);

	UFUNCTION()
	void UpdateQuest(AC_SMSQuest* Quest, int32 Index);

private:
	UPROPERTY(meta=(BindWidget))
	UWC_SMSButton* OnOffButton; // �ݱ� ��ư

	UPROPERTY(meta = (BindWidget))
	class UScrollBox* QuestGroup; // ����Ʈ ����

	// �ִϸ��̼� ���ε�
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* SlideIn;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* SlideOut;

	bool bOnMenuOpen = true;
};
