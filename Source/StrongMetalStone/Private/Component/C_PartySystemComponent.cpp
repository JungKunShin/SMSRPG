// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/C_PartySystemComponent.h"
#include "Widget/Party/WC_InvitePartyWidget.h"
#include "Widget/Ingame/WC_PlayerWidget.h"
#include "Widget/Party/WC_PartyWidget.h"
#include "HUD/C_WorldHUD.h"
#include "GameMode/C_WorldGameMode.h"
#include "C_SMSGameInstance.h"
#include "Character/C_PlayerCharacter.h"

void UC_PartySystemComponent::ServerOpenPartyInviteWidget_Implementation(AC_PlayerCharacter* Inviter, AC_PlayerCharacter* _Character)
{
	_Character->PartySytemComponent->ClientOpenPartyInviteWidget(Inviter, _Character);
}

void UC_PartySystemComponent::ClientOpenPartyInviteWidget_Implementation(AC_PlayerCharacter* Inviter, AC_PlayerCharacter* _Character)
{
	//이미 파티중이면 오지않게
	if (_Character->PartyInfo.InParty) return;

	if (!CastWHUD(GetMyHUD())) return;
	CastWHUD(GetMyHUD())->CreateMyWidget(CastWHUD(GetMyHUD())->InvitePartyWidgetClass, CastWHUD(GetMyHUD())->InvitePartyWidget);

	//화면 중심에 파티초대위젯생성
	FVector2D ScreenSize;
	GEngine->GameViewport->GetViewportSize(ScreenSize);
	CastWHUD(GetMyHUD())->InvitePartyWidget->Inviter = Inviter;
	CastWHUD(GetMyHUD())->InvitePartyWidget->TextBlock_PartyOwner->SetText(FText::FromString(Inviter->CharacterInfo.CharacterName));

}

void UC_PartySystemComponent::ServerCreateParty_Implementation(AC_PlayerCharacter* Inviter)
{
	//이미 파티에 가입되어있으면
	if (Inviter->PartyInfo.InParty) return;
	//새로운 파티 생성
	FPartyInfo NewParty; 
	NewParty.PartyGUID = FGuid::NewGuid();
	NewParty.PartyOwner = Inviter;
	NewParty.PartyPlayers.Add(Inviter);
	NewParty.InParty = true;

	//서버에 파티 등록
	CastWGM(GetMyGM())->PartyDatas.Add(NewParty);

	Inviter->PartySytemComponent->MultiUpdateParty(NewParty);
	Inviter->PartySytemComponent->ClientUpdateParty(NewParty);
}

void UC_PartySystemComponent::MultiUpdateParty_Implementation(FPartyInfo NewParty)
{	
	CastWCharacter(GetOwner())->PartyInfo = NewParty;
}

void UC_PartySystemComponent::ClientUpdateParty_Implementation(FPartyInfo NewParty)
{
	UpdateParty(NewParty);
}

void UC_PartySystemComponent::ClientExitParty_Implementation(FCharacterInfo _CharacterInfo)
{
	CastWHUD(GetMyHUD())->PlayerWidget->WBPC_PartyWidget->ExitParty(_CharacterInfo);
}

void UC_PartySystemComponent::UpdateParty(FPartyInfo NewParty)
{	
	CastWCharacter(GetOwner())->PartyInfo = NewParty;
	//위젯 업데이트
	if (CastWCharacter(GetOwner())->HasAuthority())return;
	if (!CastWHUD(GetMyHUD()))return;
	if (!CastWHUD(GetMyHUD())->PlayerWidget) return;
	CastWHUD(GetMyHUD())->PlayerWidget->WBPC_PartyWidget->SetVisibility(ESlateVisibility::Visible);
	for (UWC_OnePartyWidget* OnePartyWidget : CastWHUD(GetMyHUD())->PlayerWidget->WBPC_PartyWidget->OnePartyWidgets)
	{
		if (OnePartyWidget)
		{
			OnePartyWidget->RemoveFromParent();
			
		}

	}
	
	//파티 추가

	for (AC_PlayerCharacter* PartyPlayer : NewParty.PartyPlayers)
	{
		CastWHUD(GetMyHUD())->PlayerWidget->WBPC_PartyWidget->AddParty(PartyPlayer);
	}
	
	CastWGI(GetMyGI())->PartyInfo = NewParty;
	CastWGI(GetMyGI())->PartyData= PartyInfoToData(NewParty);
}

void UC_PartySystemComponent::ServerPartyAddCharacter_Implementation(AC_PlayerCharacter* PartyOwner,AC_PlayerCharacter* Invited)
{	
	PartyOwner->PartyInfo.PartyPlayers.Add(Invited);
	CastWCharacter(GetOwner())->PartyInfo = PartyOwner->PartyInfo;
	Invited->PartyInfo = PartyOwner->PartyInfo;

	//파티 갱신
	for (FPartyInfo& Party : CastWGM(GetMyGM())->PartyDatas)
	{
		if (PartyOwner == Party.PartyOwner)
		{
			Party = PartyOwner->PartyInfo;
		}
	}
	for (AC_PlayerCharacter* PartyPlayer : PartyOwner->PartyInfo.PartyPlayers)
	{
		PartyPlayer->PartySytemComponent->MultiUpdateParty(PartyOwner->PartyInfo);
		PartyPlayer->PartySytemComponent->ClientUpdateParty(PartyOwner->PartyInfo);
	}
	

}

FPartyData UC_PartySystemComponent::PartyInfoToData(FPartyInfo PartyInfo)
{
	FPartyData PartyData;



	PartyData.InParty = PartyInfo.InParty;
	PartyData.PartyGUID = PartyInfo.PartyGUID;

	for (AC_PlayerCharacter* PartyCharacter : PartyInfo.PartyPlayers)
	{

		if (!PartyCharacter) continue;
		PartyData.PartyPlayersName.Add(PartyCharacter->CharacterInfo.CharacterName);
	}

	if (!PartyInfo.PartyOwner) return PartyData;
	PartyData.PartyOwnerName = PartyInfo.PartyOwner->CharacterInfo.CharacterName;


	return PartyData;
}

FPartyInfo UC_PartySystemComponent::PartyDataToInfo(AC_WorldGameMode* GM, FPartyData PartyData)
{
	FPartyInfo PartyInfo;

	if (!PartyData.InParty) return PartyInfo;

	PartyInfo.InParty = PartyData.InParty;
	PartyInfo.PartyGUID = PartyData.PartyGUID;

	for (AC_PlayerCharacter* Character : GM->Characters)
	{
		//이름이 일치하는것을 찾으면
		if (Character->CharacterInfo.CharacterName == PartyData.PartyOwnerName)
		{
			PartyInfo.PartyOwner = Character;
		}
		if (PartyData.PartyPlayersName.Contains(Character->CharacterInfo.CharacterName))
		{
			PartyInfo.PartyPlayers.Add(Character);
		}
	}

	return PartyInfo;
}



