// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrBaseAttackSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

void AC_WrBaseAttackSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (Character == nullptr)
		Character = CastWCharacter(GetMyCharacter());

	++SkillCombo; // 스킬 콤보 증가

	AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Character->GetController());
	WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
	GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);

	if (SkillCombo == 1) // 스킬 콤보가 1이라면
	{
		if (UKismetMathLibrary::VSize(Character->GetVelocity()) < KINDA_SMALL_NUMBER)
		{
			Character->ServerPlayMontage(SkillAsset->ExtraSkillMontage,"FullOne"); // 설정한 별도의 몽타주 FullOne 실행
		}
		else
		{
			Character->ServerPlayMontage(SkillAsset->SkillMontage); // 설정한 몽타주 Default 실행
		}
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrBaseAttackSkillINS::AttackIMCReset, FIRST_ATTACK_RETURN, false);
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AC_WrBaseAttackSkillINS::SkillComboReset, FIRST_COMBO_TIME, false);
	}
	else if (SkillCombo == 2) // 스킬 콤보가 2라면
	{
		if (UKismetMathLibrary::VSize(Character->GetVelocity()) < KINDA_SMALL_NUMBER)
		{
			Character->ServerPlayMontage(SkillAsset->ExtraSkillMontage, "FullTwo"); // 설정한 별도의 몽타주 FullOne 실행
		}
		else
		{
			Character->ServerPlayMontage(SkillAsset->SkillMontage, "Second"); // 설정한 몽타주 "Second" 실행
		}
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrBaseAttackSkillINS::AttackIMCReset, SECOND_ATTACK_RETURN, false);
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AC_WrBaseAttackSkillINS::SkillComboReset, SECOND_COMBO_TIME, false);
	}
	else if (SkillCombo == 3) // 스킬 콤보가 3이라면
	{
		Character->ServerPlayMontage(SkillAsset->ExtraSkillMontage); // 설정한 별도의 몽타주 Default 실행
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrBaseAttackSkillINS::AttackIMCReset, THIRD_ATTACK_RETURN, false);
	}
}
