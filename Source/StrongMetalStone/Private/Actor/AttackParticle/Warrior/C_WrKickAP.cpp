// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Warrior/C_WrKickAP.h"
#include "C_SMSGameInstance.h"
#include "Character/C_Boss.h"

AC_WrKickAP::AC_WrKickAP()
{
	Damage = 3.0f; // ������ 1.0
	SphereRadius = 150.0f; // Ʈ���̽� ���� ������ 1.5m
	DelayTime = 0.5f; // AP �ı� �ð�
	ShakeDegree = 1.0f; // ī�޶� ��鸲 ����
}

void AC_WrKickAP::BeginPlay()
{
	Super::BeginPlay();
	EffectClass = GetMyEffectManager()->StunEffectClass;

	ApplyDamage();

	if (bOnHitEnemy)
	{
		for (int i = 0; i < HitEnemies.Num(); ++i)
		{
			AC_SMSCharacter* KnockBackEnemy = HitEnemies[i];
			if (Cast<AC_Boss>(KnockBackEnemy))continue;
			ServerKnockBack(KnockBackEnemy);
		}
	
	}
}

void AC_WrKickAP::ServerKnockBack_Implementation(AC_SMSCharacter*_HitEnemy)
{
	HitEnemy = _HitEnemy;
	FVector LaunchVelocity = Owner->GetActorForwardVector() * KNOCKBACK_STREANGTH;
	LaunchVelocity.Z = 300.0f;
	HitEnemy->LaunchCharacter(LaunchVelocity, true, true);
}
