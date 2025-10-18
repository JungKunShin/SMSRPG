// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrKickSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_WrKickSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());

		// 쿨타임 시작
		OnCool = false;
		OnTriggerCooldown.Broadcast(this);
		OnStartCooldown.Broadcast(this);

		// 쿨타임 타이머
		DelayCoolTime();

		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Character->GetController());
		WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
		GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrKickSkillINS::AttackIMCReset, ATTACK_RETURN, false);
		Character->ServerPlayMontage(SkillAsset->SkillMontage, "Kick");
	}
}
