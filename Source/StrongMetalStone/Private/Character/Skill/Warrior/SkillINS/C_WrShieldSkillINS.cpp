// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrShieldSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Warrior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_WrShieldSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());
		
		OnTriggerCooldown.Broadcast(this);

		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Character->GetController());
		WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
		Character->ServerPlayMontage(SkillAsset->SkillMontage, "Shield"); // ������ ��Ÿ�� "Shield" ����

		BasicWalkSpeed = Character->GetCharacterMovement()->MaxWalkSpeed; // ���� �ȱ� �ӵ� ����
		Character->GetCharacterMovement()->MaxWalkSpeed = CHARGING_WALK_SPEED; // ��¡�ȱ�ӵ��� ��ȯ
		CastWCharacter(Character)->ServerWalk(); // ������ �ӵ� ��ȯ
		CastWCharacter(Character)->ServerOnShield();
		GetWorld()->GetTimerManager().ClearTimer(ShieldOffTH);
		CastWCharacter(Character)->bOnShield = true;
	}
}

void AC_WrShieldSkillINS::Holding(AC_SMSCharacter* Character)
{
	Super::Holding(Character);
}

void AC_WrShieldSkillINS::EndHold(AC_SMSCharacter* Character)
{
	if (Character == nullptr)
		Character = CastWCharacter(GetMyCharacter());

	if (CastWCharacter(Character)->bOnShield)
	{
		OnStartCooldown.Broadcast(this);
		Character->ServerStopMontage(); // ��Ÿ�� ���߱�
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Character->GetController());
		WPC->Subsystem->AddMappingContext(WPC->AttackIMC,0);
		Character->GetCharacterMovement()->MaxWalkSpeed = BasicWalkSpeed; // ���� �ȱ� �ӵ��� ��ȯ
		CastWCharacter(Character)->ServerRun(); // ������ �ӵ� ��ȯ
		CastWCharacter(Character)->ServerOnShield();
		CastWCharacter(Character)->bOnShield = false;
		OnCool = false;
		DelayCoolTime();
	}
}