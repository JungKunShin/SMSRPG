// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Mage/C_MgHeliosPulseAP.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Character/C_Boss.h"
#include "GameFramework/CharacterMovementComponent.h"

AC_MgHeliosPulseAP::AC_MgHeliosPulseAP()
{
	Damage = 1.0f; // 데미지 
	SphereRadius = 1200.0f; // 트레이스 범위 반지름 10m
	DelayTime = 5.0f; // AP 파괴 시간
	InitShakeDegree = 5.0f;
	ShakeDegree = 2.0f; // 카메라 흔들림 정도
	AttackEffects = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	AttackEffects->SetupAttachment(RootComponent);
}

void AC_MgHeliosPulseAP::BeginPlay()
{

	Super::BeginPlay();
	AC_WorldPlayerController* WorldController = Cast<AC_WorldPlayerController>(Owner->GetController());
	if (!WorldController)return;
	WorldController->PlayerCameraManager->StartCameraShake(UC_AttackCameraShake::StaticClass(), InitShakeDegree);
	Damage *= Owner->CharacterInfo.Damage;
	GetWorld()->GetTimerManager().SetTimer(AttackTH, this, &AC_MgHeliosPulseAP::DelayAttack, AttackDelay, false);
}

void AC_MgHeliosPulseAP::DelayAttack()
{
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

void AC_MgHeliosPulseAP::ServerKnockBack_Implementation(AC_SMSCharacter* _HitEnemy)
{
	HitEnemy = _HitEnemy;

	FVector EnemyLocation = HitEnemy->GetActorLocation();
	FVector OwnerLocation = Owner->GetActorLocation();
	FVector Direction = (OwnerLocation - EnemyLocation).GetSafeNormal();

	FVector LaunchVelocity = -Direction * KNOCKBACK_STREANGTH;
	if (FVector::Dist(EnemyLocation, OwnerLocation) < CLOSE_RANGE)
	{
		Damage *= (Owner->CharacterInfo.Damage*2);
		LaunchVelocity = -Direction * STRONGER_KNOCKBACK_STREANGTH;
		LaunchVelocity.Z = 900.0f;
	}
	else
	{
		Damage *= (Owner->CharacterInfo.Damage);
		LaunchVelocity.Z = 700.0f;
	}


	HitEnemy->GetCharacterMovement()->StopMovementImmediately();
	HitEnemy->ServerStopMontage();
	HitEnemy->LaunchCharacter(LaunchVelocity, true, true);
}
