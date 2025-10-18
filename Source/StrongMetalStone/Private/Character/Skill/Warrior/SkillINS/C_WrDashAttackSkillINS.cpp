// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrDashAttackSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "Effect/EffectINS/C_ElectricEffectINS.h"
#include "PlayerState/C_WorldPlayerState.h"
#include "C_SMSGameInstance.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_WrDashAttackSkillINS::AC_WrDashAttackSkillINS()
{
}

void AC_WrDashAttackSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());
		if (!CastWCharacter(Character)->TargetCharacter) return;

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());
		
		if (Player->CharacterInfo.Curmp >= DemandedMana)
		{
			OnTriggerCooldown.Broadcast(this);
			OnStartCooldown.Broadcast(this);

			OnCool = false;
			DelayCoolTime();
			WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
			GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrDashAttackSkillINS::AttackIMCReset, ATTACK_RETURN, false);
			Character->ServerPlayMontage(SkillAsset->SkillMontage, "DashAttack"); // 설정한 몽타주 "Second" 섹션 실행
			Player->CharacterInfo.Curmp -= DemandedMana;
			Player->Update();
		}
	}
}
