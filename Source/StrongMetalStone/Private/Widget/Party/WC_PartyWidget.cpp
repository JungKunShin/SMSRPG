// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Party/WC_PartyWidget.h"
#include "Widget/Party/WC_OnePartyWidget.h"
#include "Character/C_PlayerCharacter.h"
#include "C_SMSGameInstance.h"

void UWC_PartyWidget::AddParty(AC_PlayerCharacter* Character)
{
	if (!Character) return;
	if (Cast<UWC_OnePartyWidget>(CreateWidget<UUserWidget>(GetOwningPlayer(), OnePartyWidgetClass)))
	{		
		UWC_OnePartyWidget* OnePartyWidget = Cast<UWC_OnePartyWidget>(CreateWidget<UUserWidget>(GetOwningPlayer(), OnePartyWidgetClass));
		OnePartyWidgets.Add(OnePartyWidget);
		OnePartyWidget->AddToViewport();		

		VerticalBox_Party->AddChild(OnePartyWidget);		
		OnePartyWidget->NickName = Character->CharacterInfo.CharacterName;
		OnePartyWidget->job = Character->CharacterInfo.Job;
		OnePartyWidget->HpBarUpdate(Character->CharacterInfo.Curhp/Character->CharacterInfo.Maxhp);

		if (CastWGI(GetMyGI())->PartyInfo.PartyOwner == Character)
		{
			OnePartyWidget->Image_Owner->SetVisibility(ESlateVisibility::Visible);
		}

		OnePartyWidget->SetWidget();
	}
}

void UWC_PartyWidget::ExitParty(FCharacterInfo CharacterInfo)			
{
	for (UWidget* PartyWidget : VerticalBox_Party->GetAllChildren())
	{
		if (Cast<UWC_OnePartyWidget>(PartyWidget)->NickName == CharacterInfo.CharacterName)
			PartyWidget->RemoveFromParent();
	}
}

void UWC_PartyWidget::Update()
{
	if (!CastWCharacter(GetMyCharacter())->PartyInfo.InParty)return;

	for(AC_PlayerCharacter* PartyPlayer : CastWCharacter(GetMyCharacter())->PartyInfo.PartyPlayers)
	{
		if(PartyPlayer)
		UpdateHp(PartyPlayer);
	}
}

void UWC_PartyWidget::UpdateHp(AC_PlayerCharacter* PartyPlayer)
{
	for (UWC_OnePartyWidget* OnePartyWidget : OnePartyWidgets)
	{
		if (OnePartyWidget->NickName == PartyPlayer->CharacterInfo.CharacterName)
		{
			OnePartyWidget->HpBarUpdate(PartyPlayer->CharacterInfo.Curhp / PartyPlayer->CharacterInfo.Maxhp);
		}
	}
}
