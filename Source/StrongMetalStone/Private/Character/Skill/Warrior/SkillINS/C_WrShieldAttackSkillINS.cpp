// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrShieldAttackSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Character/C_Warrior.h"
#include "HUD/C_WorldHUD.h"

void AC_WrShieldAttackSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());

		if (Player->CharacterInfo.Curmp >= DemandedMana)
		{
			OnTriggerCooldown.Broadcast(this);
			OnStartCooldown.Broadcast(this);
			OnCool = false;
			DelayCoolTime();

			Cast<AC_Warrior>(Player)->DelayOverHeat();
			WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
			GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrShieldAttackSkillINS::AttackIMCReset, ATTACK_RETURN, false);
			Character->ServerPlayMontage(SkillAsset->SkillMontage);
			Player->CharacterInfo.Curmp -= DemandedMana;
			Player->Update();
		}
	}
}
