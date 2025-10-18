// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Mage/SkillIns/C_MgManaChargeSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_MgManaChargeSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());

		WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
		GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_MgManaChargeSkillINS::AttackIMCReset, ATTACK_RETURN, false);
		Character->ServerPlayMontage(SkillAsset->SkillMontage);
		OnTriggerCooldown.Broadcast(this);
		bOnStart = true;
	}
}

void AC_MgManaChargeSkillINS::EndHold(AC_SMSCharacter* Character)
{
	if (OnCool&&bOnStart)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		Character->ServerStopMontage();
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Character->GetController());

		AttackIMCReset();

		OnCool = false;
		OnStartCooldown.Broadcast(this);

		DelayCoolTime();
		bOnStart = false;
	}
}
