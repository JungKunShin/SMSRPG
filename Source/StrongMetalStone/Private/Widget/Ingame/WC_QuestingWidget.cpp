// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_QuestingWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_PlayerCharacter.h"
#include "HUD/C_WorldHUD.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Quest/C_SMSQuest.h"
#include "Widget/Ingame/WC_QuestingTextWidget.h"



void UWC_QuestingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 닫기 버튼 초기화
	OnOffButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/btn_icon_align_vertical.btn_icon_align_vertical")), FVector3f(1.f, 1.f, 1.f));
	// 닫기 버튼에 함수 바인딩
	OnOffButton->OnButtonClicked.AddDynamic(this, &UWC_QuestingWidget::OnOffButtonClicked);
}

void UWC_QuestingWidget::OnOffButtonClicked()
{
	if (!SlideIn || !SlideOut)
	{
		return;
	}

	if (!bOnMenuOpen)
	{
		if (QuestGroup)
		{
			QuestGroup->SetVisibility(ESlateVisibility::Visible);
		}

		PlayAnimation(SlideIn);
	}
	else
	{
		if (QuestGroup)
		{
			QuestGroup->SetVisibility(ESlateVisibility::Hidden);
		}

		PlayAnimation(SlideOut);
	}
	bOnMenuOpen = !bOnMenuOpen;
}

void UWC_QuestingWidget::SetQuest(UWC_QuestingTextWidget* QuestText)
{
	QuestGroup->AddChild(QuestText);
	QuestGroup->bAnimateWheelScrolling = true;
}

void UWC_QuestingWidget::RemoveQuest(int32 Index)
{
	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	AC_WorldHUD* HUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	QuestGroup->RemoveChildAt(Index);
	if (Character->QuestArr.IsEmpty())
	{
		HUD->SetQuestingWidgetVisible(false);
	}
}

void UWC_QuestingWidget::UpdateQuest(AC_SMSQuest* Quest, int32 Index)
{
	UWC_QuestingTextWidget* QuestText = Cast< UWC_QuestingTextWidget>(QuestGroup->GetChildAt(Index));

	if (QuestText)
	{
		QuestText->UpdateText(Quest);
	}
}
