// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Warrior/C_WrExplosionWaveAP.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_WrExplosionWaveAP::AC_WrExplosionWaveAP()
{
	Damage = 5.0f; // 데미지 3.0
	SphereRadius = 250.0f; // 트레이스 범위 반지름 2.5m
	DelayTime = 0.5f; // AP 파괴 시간
	ShakeDegree = 1.5f;
}

void AC_WrExplosionWaveAP::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AC_PlayerCharacter>(GetOwner());
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Owner->GetController());
	if (!WPC)return;
	Damage = Owner->CharacterInfo.Damage * 5.0f* AdjustedAttackRate;

	if(WPC->Subsystem)
	ApplyDamage();
}
