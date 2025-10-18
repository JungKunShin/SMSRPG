// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Warrior/C_WrBaseAttackAP.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_WrBaseAttackAP::AC_WrBaseAttackAP()
{
	Damage = 0.0f; // 데미지 1.0
	SphereRadius = 150.0f; // 트레이스 범위 반지름 1.5m
	DelayTime = 0.5f; // AP 파괴 시간
	ShakeDegree = 1.0f;
}

void AC_WrBaseAttackAP::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AC_PlayerCharacter>(GetOwner());
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Owner->GetController());
	if (!WPC)return;
	if (!Owner->SkillSytemComponent->CurSkill) return;

	if (WPC->Subsystem && Owner->SkillSytemComponent->CurSkill->SkillCombo == 1) // 기본공격 콤보가 1이라면
	{
		Damage = Owner->CharacterInfo.Damage * 1.0f*AdjustedAttackRate;
		ShakeDegree = 1.2f;
	}
	else if (WPC->Subsystem && Owner->SkillSytemComponent->CurSkill->SkillCombo == 2) // 기본공격 콤보가 2이라면
	{
		Damage = Owner->CharacterInfo.Damage * 1.5f* AdjustedAttackRate;
		ShakeDegree = 1.2f;
	}
	else if (WPC->Subsystem && Owner->SkillSytemComponent->CurSkill->SkillCombo == 3) // 기본공격 콤보가 3이라면
	{
		Damage = Owner->CharacterInfo.Damage * 2.0f* AdjustedAttackRate;
		ShakeDegree = 1.5f;
	}

	ApplyDamage();
}
