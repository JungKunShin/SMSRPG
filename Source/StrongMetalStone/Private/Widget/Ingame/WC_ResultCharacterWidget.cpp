// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_ResultCharacterWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UWC_ResultCharacterWidget::UpdateText(FString nickName, unsigned int Damage, unsigned int Level)
{
	TEXT_NickName->SetText(FText::FromString(nickName));
	TEXT_Level->SetText(FText::AsNumber(Level));
	TEXT_AllDamageAmount->SetText(FText::AsNumber(Damage));
}

void UWC_ResultCharacterWidget::UpdateImage(EPlayerJob Job)
{
	if (Job == EPlayerJob::WARRIOR)
	{
		Image_Job->SetBrushFromTexture(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/01_Character/icon_warrior.icon_warrior")),true);
	}
	else if(Job== EPlayerJob::MAGE)
	{
		Image_Job->SetBrushFromTexture(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/01_Character/icon_mage.icon_mage")), true);

	}
}
