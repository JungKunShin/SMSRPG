// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrBaseAttackSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

void AC_WrBaseAttackSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (Character == nullptr)
		Character = CastWCharacter(GetMyCharacter());

	++SkillCombo; // ��ų �޺� ����

	AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Character->GetController());
	WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
	GetWorld()->GetTimerManager().ClearTimer(AttackIMCTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);

	if (SkillCombo == 1) // ��ų �޺��� 1�̶��
	{
		if (UKismetMathLibrary::VSize(Character->GetVelocity()) < KINDA_SMALL_NUMBER)
		{
			Character->ServerPlayMontage(SkillAsset->ExtraSkillMontage,"FullOne"); // ������ ������ ��Ÿ�� FullOne ����
		}
		else
		{
			Character->ServerPlayMontage(SkillAsset->SkillMontage); // ������ ��Ÿ�� Default ����
		}
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrBaseAttackSkillINS::AttackIMCReset, FIRST_ATTACK_RETURN, false);
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AC_WrBaseAttackSkillINS::SkillComboReset, FIRST_COMBO_TIME, false);
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
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrBaseAttackSkillINS::AttackIMCReset, SECOND_ATTACK_RETURN, false);
		GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AC_WrBaseAttackSkillINS::SkillComboReset, SECOND_COMBO_TIME, false);
	}
	else if (SkillCombo == 3) // ��ų �޺��� 3�̶��
	{
		Character->ServerPlayMontage(SkillAsset->ExtraSkillMontage); // ������ ������ ��Ÿ�� Default ����
		GetWorld()->GetTimerManager().SetTimer(AttackIMCTimerHandle, this, &AC_WrBaseAttackSkillINS::AttackIMCReset, THIRD_ATTACK_RETURN, false);
	}
}
