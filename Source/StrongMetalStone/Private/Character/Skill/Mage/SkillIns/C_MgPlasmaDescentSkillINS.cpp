#include "Character/Skill/Mage/SkillIns/C_MgPlasmaDescentSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

void AC_MgPlasmaDescentSkillINS::StartOnce(AC_SMSCharacter* Character)
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
			WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
			GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_MgPlasmaDescentSkillINS::AttackIMCReset, ATTACK_RETURN, false);
			OnCool = false;
			OnTriggerCooldown.Broadcast(this);
			OnStartCooldown.Broadcast(this);
			DelayCoolTime();
			Character->ServerPlayMontage(SkillAsset->SkillMontage, "PlasmaDescent");
			Player->CharacterInfo.Curmp -= DemandedMana;
			Player->Update();
		}
	}
}