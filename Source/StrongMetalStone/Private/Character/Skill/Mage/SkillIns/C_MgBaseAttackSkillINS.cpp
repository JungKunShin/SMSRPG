// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Mage/SkillIns/C_MgBaseAttackSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_MgBaseAttackSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (Character == nullptr)
		Character = CastWCharacter(GetMyCharacter());
	if (!CastWCharacter(Character)->TargetCharacter)return;

	++SkillCombo; // ��ų �޺� ����

	AC_PlayerCharacter* Player = CastWCharacter(Character);
	AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());
	WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
	GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);

	if (SkillCombo == 1) // ��ų �޺��� 1�̶��
	{
		if (UKismetMathLibrary::VSize(Character->GetVelocity()) < KINDA_SMALL_NUMBER)
		{
			Character->ServerPlayMontage(SkillAsset->ExtraSkillMontage); // ������ ������ ��Ÿ�� FullOne ����
		}
		else
		{
			Character->ServerPlayMontage(SkillAsset->SkillMontage); // ������ ��Ÿ�� Default ����
		}
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_MgBaseAttackSkillINS::AttackIMCReset, FIRST_ATTACK_RETURN, false);
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AC_MgBaseAttackSkillINS::SkillComboReset, FIRST_COMBO_TIME, false);
	}
	else if (SkillCombo == 2) // ��ų �޺��� 2���
	{
		if (UKismetMathLibrary::VSize(Character->GetVelocity()) < KINDA_SMALL_NUMBER)
		{
			Character->ServerPlayMontage(SkillAsset->ExtraSkillMontage, "FullTwo"); // ������ ������ ��Ÿ�� FullOne ����
		}
		else
		{
			Character->ServerPlayMontage(SkillAsset->SkillMontage, "Second"); // ������ ��Ÿ�� "Second" ����
		}
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_MgBaseAttackSkillINS::AttackIMCReset, SECOND_ATTACK_RETURN, false);
	}
}
