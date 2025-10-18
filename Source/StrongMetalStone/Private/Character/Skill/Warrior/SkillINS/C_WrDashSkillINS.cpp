// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrDashSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_WrDashSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());

		OnCool = false;
		DelayCoolTime();

		WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
		GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrDashSkillINS::AttackIMCReset, ATTACK_RETURN, false);
		Character->ServerPlayMontage(SkillAsset->SkillMontage);
	}
}
