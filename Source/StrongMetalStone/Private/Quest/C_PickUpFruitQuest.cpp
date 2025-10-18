// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/C_PickUpFruitQuest.h"

AC_PickUpFruitQuest::AC_PickUpFruitQuest()
{
	if (QuestDataTable)
	{
        FName RowName = FName(TEXT("PickUpFruit")); // �� ������ ���̺��� ã�� ���� ���� �̸�
        FQuestData* Row = QuestDataTable->FindRow<FQuestData>(RowName, TEXT("FindNameRow"));

        if (Row)
        {
            QuestData.QuestTitle = Row->QuestTitle;
            QuestData.QuestInfo = Row->QuestInfo;
            QuestData.Reward = Row->Reward;
            QuestData.CompletedCondition = Row->CompletedCondition;
            QuestData.Questting = Row->Questting;
            QuestData.FinishConversation = Row->FinishConversation;

        }
	}
    ObjectNum = 5;
    QuestName = "PickUpFruit";
}
