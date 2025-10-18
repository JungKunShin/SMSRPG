// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrSlashSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_WrSlashSkillINS::AC_WrSlashSkillINS()
{
}

void AC_WrSlashSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());

		if (Player->CharacterInfo.Curmp >= DemandedMana)
		{
			OnStartCooldown.Broadcast(this);
			OnCool = false;
			DelayCoolTime();
			GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AC_WrSlashSkillINS::SkillComboReset, COMBO_RESET_TIME, false);

			AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());
			WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
			GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrSlashSkillINS::AttackIMCReset, ATTACK_RETURN, false);
			Character->ServerPlayMontage(SkillAsset->SkillMontage);
			Player->CharacterInfo.Curmp -= DemandedMana;
			Player->Update();
		}
	}
}
