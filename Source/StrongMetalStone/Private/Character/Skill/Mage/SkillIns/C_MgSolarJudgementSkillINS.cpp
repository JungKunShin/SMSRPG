#include "Character/Skill/Mage/SkillIns/C_MgSolarJudgementSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_MgSolarJudgementSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());

		if (Player->CharacterInfo.Curmp >= DemandedMana)
		{
			WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
			GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_MgSolarJudgementSkillINS::AttackIMCReset, ATTACK_RETURN, false);
			OnCool = false;
			OnTriggerCooldown.Broadcast(this);
			OnStartCooldown.Broadcast(this);

			DelayCoolTime();

			Character->ServerPlayMontage(SkillAsset->SkillMontage, "SolarJudgement");
			Player->CharacterInfo.Curmp -= DemandedMana;
			Player->Update();
		}

	}
}