// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/C_SMSActorComponent.h"
#include "C_PartySystemComponent.generated.h"

class AC_PlayerCharacter;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_PartySystemComponent : public UC_SMSActorComponent
{
	GENERATED_BODY()
	

public:
	//파티초대 위젯 생성
	UFUNCTION(Server, Reliable)
	void ServerOpenPartyInviteWidget(AC_PlayerCharacter* Inviter, AC_PlayerCharacter* _Character);

	UFUNCTION(Client, Reliable)
	void ClientOpenPartyInviteWidget(AC_PlayerCharacter* Inviter, AC_PlayerCharacter* _Character);

	//파티추가
	UFUNCTION(Server, Reliable)
	void ServerPartyAddCharacter(AC_PlayerCharacter* PartyOwner, AC_PlayerCharacter* Invited);

	//파티생성
	UFUNCTION(Server, Reliable)
	void ServerCreateParty(AC_PlayerCharacter* Inviter);

	//파티 업데이트
	UFUNCTION(NetMulticast, Reliable)
	void MultiUpdateParty(FPartyInfo NewParty);

	UFUNCTION(Client, Reliable)
	void ClientUpdateParty(FPartyInfo NewParty);

	UFUNCTION(Client, Reliable)
	void ClientExitParty(FCharacterInfo _CharacterInfo);

	void UpdateParty(FPartyInfo NewParty);

	FPartyData PartyInfoToData(FPartyInfo PartyInfo);
	FPartyInfo PartyDataToInfo(AC_WorldGameMode* GM, FPartyData PartyData);
};
