// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrExplosionWaveSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_WrExplosionWaveSkillINS::AC_WrExplosionWaveSkillINS()
{
}

void AC_WrExplosionWaveSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
	
		if (Player->CharacterInfo.Curmp >= DemandedMana)
		{
			OnCool = false;
			OnTriggerCooldown.Broadcast(this);
			OnStartCooldown.Broadcast(this);

			DelayCoolTime();

			AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Character->GetController());
			WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
			GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrExplosionWaveSkillINS::AttackIMCReset, ATTACK_RETURN, false);
			Character->ServerPlayMontage(SkillAsset->SkillMontage, "ExplosionWave"); // 설정한 몽타주 "Third" 실행
			Player->CharacterInfo.Curmp -= DemandedMana;
			Player->Update();
		}
	}
}
