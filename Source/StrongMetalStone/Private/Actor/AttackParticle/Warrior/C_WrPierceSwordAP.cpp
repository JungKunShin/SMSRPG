// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Warrior/C_WrPierceSwordAP.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_WrPierceSwordAP::AC_WrPierceSwordAP()
{
	Damage = 5.0f; // 데미지 5.0
	SphereRadius = 400.0f; // 트레이스 범위 반지름 4m
	DelayTime = 0.5f; // AP 파괴 시간
	ShakeDegree = 2.0f;
}

void AC_WrPierceSwordAP::BeginPlay()
{
	Super::BeginPlay();



	Owner = Cast<AC_PlayerCharacter>(GetOwner());

	if (!Owner->SkillSytemComponent->CurSkill) return;

	if (Owner->SkillSytemComponent->CurSkill->SkillCombo == 1)
	{
		Damage = Owner->CharacterInfo.Damage * 7.0f*AdjustedAttackRate;
		ShakeDegree = 6.0f;
	}
	else if (Owner->SkillSytemComponent->CurSkill->SkillCombo == 2)
	{
		Damage = Owner->CharacterInfo.Damage * 12.0f* AdjustedAttackRate;
		ShakeDegree = 9.0f;
	}
	else if (Owner->SkillSytemComponent->CurSkill->SkillCombo >= 3)
	{
		Damage = Owner->CharacterInfo.Damage * 20.0f* AdjustedAttackRate;
		ShakeDegree = 12.0f;
	}

	ApplyDamage();
}
