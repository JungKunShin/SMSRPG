// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Mage/C_MgHeliosAfterglowAP.h"

AC_MgHeliosAfterglowAP::AC_MgHeliosAfterglowAP()
{
	Damage = 0.1f; // 데미지 0.1
	SphereRadius = 100.0f; // 트레이스 범위 반지름 2.5m
	DelayTime = 0.3f; // AP 파괴 시간
	ShakeDegree = 5.0f; // 카메라 흔들림 정도
}

void AC_MgHeliosAfterglowAP::BeginPlay()
{
	Super::BeginPlay();
	Start = GetActorLocation() + GetActorRightVector() * -1000.0f;
	End = GetActorLocation();
	Damage *= Owner->CharacterInfo.Damage;
	ApplyDamage();
}
