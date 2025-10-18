// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Mage/C_MgPlasmaDescentAP.h"
#include"Components/DecalComponent.h"

AC_MgPlasmaDescentAP::AC_MgPlasmaDescentAP()
{
	Damage = 0.4f; // ������ 0.4
	SphereRadius = 400.0f; // Ʈ���̽� ���� ������ 4m
	DelayTime = 5.0f; // AP �ı� �ð�
	ShakeDegree = 5.0f; // ī�޶� ��鸲 ����
	//DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	//DecalComp->SetupAttachment(RootComponent);
	//DecalComp->SetVisibility(true);
}

void AC_MgPlasmaDescentAP::BeginPlay()
{
	/*EffectComponent->Deactivate();*/
	Super::BeginPlay();
	Start = GetActorLocation() + GetActorUpVector() * DOWN_HEIGHT;
	End = GetActorLocation()+ GetActorUpVector() * UP_HEIGHT;
	Damage *= Owner->CharacterInfo.Damage;
	/*GetWorld()->GetTimerManager().SetTimer(AttackTH, this, &AC_MgPlasmaDescentAP::DelayAttack, AttackDelay, false);*/
	GetWorld()->GetTimerManager().SetTimer(AttackTH, this, &AC_MgPlasmaDescentAP::AfterAttack, AfterDelay, false);
}

void AC_MgPlasmaDescentAP::DelayAttack()
{
	//DecalComp->SetVisibility(false);
	EffectComponent->Activate();
	ApplyDamage();
	GetWorld()->GetTimerManager().SetTimer(AttackTH, this, &AC_MgPlasmaDescentAP::AfterAttack, AfterDelay, false);
}

void AC_MgPlasmaDescentAP::AfterAttack()
{
	ApplyDamage();
	GetWorld()->GetTimerManager().SetTimer(AttackTH, this, &AC_MgPlasmaDescentAP::AfterAttack, AfterDelay, false);
}
