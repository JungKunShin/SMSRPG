// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Mage/SkillIns/C_MgHeliosAfterglowSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_MgHeliosAfterglowSkillINS::StartOnce(AC_SMSCharacter* Character)
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
			if (!this) return;
			bOnStart = true;
			/*WPC->bOnAttacking = true;*/
			Character->ServerPlayMontage(SkillAsset->SkillMontage,"HeliosAfterGlow");
			Player->CharacterInfo.Curmp -= DemandedMana;
			Player->Update();
		}
	}
}

void AC_MgHeliosAfterglowSkillINS::EndHold(AC_SMSCharacter* Character)
{
	if (!this) return;

	if (OnCool && bOnStart) 
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());
		/*WPC->bOnAttacking = false;*/

		Character->ServerStopMontage();
		OnCool = false;
		bOnStart = false;
		OnStartCooldown.Broadcast(this);

		DelayCoolTime();
	}
}