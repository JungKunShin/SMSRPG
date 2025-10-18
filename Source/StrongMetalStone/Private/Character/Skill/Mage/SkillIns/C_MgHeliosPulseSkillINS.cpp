#include "Character/Skill/Mage/SkillIns/C_MgHeliosPulseSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_MgHeliosPulseSkillINS::AC_MgHeliosPulseSkillINS()
{
}

void AC_MgHeliosPulseSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());

		if (Player->GetCharacterMovement()->IsFalling())return;
		if (Player->CharacterInfo.Curmp >= DemandedMana)
		{
			OnCool = false;
			OnTriggerCooldown.Broadcast(this);
			OnStartCooldown.Broadcast(this);

			DelayCoolTime();

			WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
			GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_MgHeliosPulseSkillINS::AttackIMCReset, ATTACK_RETURN, false);
			Character->ServerPlayMontage(SkillAsset->SkillMontage,"HeliosPulse");
			Player->CharacterInfo.Curmp -= DemandedMana;
			Player->Update();
		}
	}
}
