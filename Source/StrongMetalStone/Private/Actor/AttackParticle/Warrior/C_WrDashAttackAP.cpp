// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Warrior/C_WrDashAttackAP.h"
#include "C_SMSGameInstance.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_WrDashAttackAP::AC_WrDashAttackAP()
{	
	Damage = 3.0f; // 데미지 3.0
	SphereRadius = 300.0f; // 트레이스 범위 반지름 3m
	DelayTime = 1.0f; // AP 파괴 시간
	ShakeDegree = 5.0f;
}

void AC_WrDashAttackAP::BeginPlay()
{
	Super::BeginPlay();
	EffectClass = GetMyEffectManager()->ElectricEffectClass;
	Damage = Owner->CharacterInfo.Damage * 2.5f* AdjustedAttackRate;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Owner->GetController());
	if (!WPC)return;



	ApplyDamage();
}
