// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Warrior/C_WrSlashAP.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_WrSlashAP::AC_WrSlashAP()
{
	Damage = 3.0f; // 데미지 1.0
	SphereRadius = 200.0f; // 트레이스 범위 반지름 1.5m
	DelayTime = 0.5f; // AP 파괴 시간
	ShakeDegree = 4.0f; // 카메라 흔들림 정도
}

void AC_WrSlashAP::BeginPlay()
{
	Super::BeginPlay();

	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Owner->GetController());
	if (!WPC)return;


	Damage = Owner->CharacterInfo.Damage * 3.5f * AdjustedAttackRate;
	ShakeDegree = 3.0f;

	//if (!Owner->SkillSytemComponent->CurSkill) return;
	//
	//if (WPC->Subsystem && Owner->SkillSytemComponent->CurSkill->SkillCombo == 1) // 기본공격 콤보가 1이라면
	//{
	//	Damage = Owner->CharacterInfo.Damage * 2.5f * AdjustedAttackRate;
	//	ShakeDegree = 3.0f;
	//}
	//else if (WPC->Subsystem && Owner->SkillSytemComponent->CurSkill->SkillCombo == 2) // 기본공격 콤보가 2이라면
	//{
	//	Damage = Owner->CharacterInfo.Damage * 3.0f * AdjustedAttackRate;
	//	ShakeDegree = 3.0f;
	//}
	//else if (WPC->Subsystem && Owner->SkillSytemComponent->CurSkill->SkillCombo == 3) // 기본공격 콤보가 3이라면
	//{
	//	Damage = Owner->CharacterInfo.Damage * 4.0f * AdjustedAttackRate;
	//	ShakeDegree = 4.5f;
	//}
	
	ApplyDamage();
}