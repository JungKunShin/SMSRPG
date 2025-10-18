#include "Character/Skill/Mage/SkillIns/C_MgAegisOfMinosSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_MgAegisOfMinosSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());

		OnCool = false;
		OnTriggerCooldown.Broadcast(this);
		OnStartCooldown.Broadcast(this);

		DelayCoolTime();

		WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
		GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_MgAegisOfMinosSkillINS::AttackIMCReset, ATTACK_RETURN, false);
		Character->ServerPlayMontage(SkillAsset->SkillMontage, "AegisOfMinos");

	}
}
