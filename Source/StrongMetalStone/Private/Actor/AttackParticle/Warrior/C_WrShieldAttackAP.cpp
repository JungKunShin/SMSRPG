// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Warrior/C_WrShieldAttackAP.h"
#include "C_SMSGameInstance.h"

AC_WrShieldAttackAP::AC_WrShieldAttackAP()
{
	Damage = 0.1f; // ������ 2.0
	SphereRadius = 200.0f; // Ʈ���̽� ���� ������ 2.0m
	DelayTime = 0.5f; // AP �ı� �ð�
	ShakeDegree = 1.5f;
}

void AC_WrShieldAttackAP::BeginPlay()
{
	Super::BeginPlay();
	EffectClass = GetMyEffectManager()->PowerStunEffectClass;
	Damage = Owner->CharacterInfo.Damage * 0.1f* AdjustedAttackRate;

	ApplyDamage();
}
