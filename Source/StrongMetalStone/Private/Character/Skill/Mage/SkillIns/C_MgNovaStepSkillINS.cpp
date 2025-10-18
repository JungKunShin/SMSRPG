#include "Character/Skill/Mage/SkillIns/C_MgNovaStepSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_MgNovaStepSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());


		if (CastWCharacter(Character))
		{
			if (Player->CharacterInfo.Curmp >= DemandedMana)
			{
				OnTriggerCooldown.Broadcast(this);
				OnStartCooldown.Broadcast(this);

				OnCool = false;
				DelayCoolTime();

				WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
				GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
				GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_MgNovaStepSkillINS::AttackIMCReset, ATTACK_RETURN, false);
				Character->ServerPlayMontage(SkillAsset->SkillMontage);
				Player->CharacterInfo.Curmp -= DemandedMana;
				Player->Update();
			}
		}
	}
}
