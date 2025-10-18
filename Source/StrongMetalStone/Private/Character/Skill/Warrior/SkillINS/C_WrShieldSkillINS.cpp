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
		Character->ServerPlayMontage(SkillAsset->SkillMontage, "Shield"); // 설정한 몽타주 "Shield" 실행

		BasicWalkSpeed = Character->GetCharacterMovement()->MaxWalkSpeed; // 기존 걷기 속도 저장
		Character->GetCharacterMovement()->MaxWalkSpeed = CHARGING_WALK_SPEED; // 차징걷기속도로 변환
		CastWCharacter(Character)->ServerWalk(); // 서버도 속도 변환
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
		Character->ServerStopMontage(); // 몽타주 멈추기
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Character->GetController());
		WPC->Subsystem->AddMappingContext(WPC->AttackIMC,0);
		Character->GetCharacterMovement()->MaxWalkSpeed = BasicWalkSpeed; // 기존 걷기 속도로 변환
		CastWCharacter(Character)->ServerRun(); // 서버도 속도 변환
		CastWCharacter(Character)->ServerOnShield();
		CastWCharacter(Character)->bOnShield = false;
		OnCool = false;
		DelayCoolTime();
	}
}