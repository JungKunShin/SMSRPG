#include "Character/Skill/Mage/SkillIns/C_MgTeleportSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_MgTeleportSkillINS::StartOnce(AC_SMSCharacter* Character)
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
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_MgTeleportSkillINS::AttackIMCReset, ATTACK_RETURN, false);
		Character->ServerPlayMontage(SkillAsset->SkillMontage);
		
	}
}
