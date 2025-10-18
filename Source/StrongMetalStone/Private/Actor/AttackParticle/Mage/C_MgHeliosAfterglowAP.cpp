// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Mage/C_MgHeliosAfterglowAP.h"

AC_MgHeliosAfterglowAP::AC_MgHeliosAfterglowAP()
{
	Damage = 0.1f; // ������ 0.1
	SphereRadius = 100.0f; // Ʈ���̽� ���� ������ 2.5m
	DelayTime = 0.3f; // AP �ı� �ð�
	ShakeDegree = 5.0f; // ī�޶� ��鸲 ����
}

void AC_MgHeliosAfterglowAP::BeginPlay()
{
	Super::BeginPlay();
	Start = GetActorLocation() + GetActorRightVector() * -1000.0f;
	End = GetActorLocation();
	Damage *= Owner->CharacterInfo.Damage;
	ApplyDamage();
}
