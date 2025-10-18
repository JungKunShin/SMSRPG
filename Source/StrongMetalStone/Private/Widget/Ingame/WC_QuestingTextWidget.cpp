// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_QuestingTextWidget.h"
#include "Quest/C_SMSQuest.h"
#include "Components/TextBlock.h"

void UWC_QuestingTextWidget::UpdateText(AC_SMSQuest* Quest)
{
	FText Text1 = FText::FromString(TEXT(" : "));
	FText Text2 = FText::FromString(TEXT(" / "));


	FText Result = FText::Format(FText::FromString("{0} {1} {2} {3} {4}"), Quest->QuestData.QuestTitle, Text1, Quest->QuestData.CurNum, Text2, Quest->ObjectNum);
	if (TEXT_QuestCondition)
	{
		TEXT_QuestCondition->SetText(Result);
	}

}
