// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/Mage/C_MgNovaStepPr.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "C_SMSGameInstance.h"

AC_MgNovaStepPr::AC_MgNovaStepPr()
{
	Damage = 3.0f; // 데미지 3.0
	DelayTime = 2.0f; // AP 파괴 시간
	ShakeDegree = 1.0f;

	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bShouldBounce = false;
}

void AC_MgNovaStepPr::BeginPlay()
{
	Super::BeginPlay();
	EffectClass = GetMyEffectManager()->StunEffectClass;
	Damage *= Owner->CharacterInfo.Damage;
}

void AC_MgNovaStepPr::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnAttackOverlap(OverlappedComponent, OtherActor, OtherComp,OtherBodyIndex, bFromSweep, SweepResult);

	if (bFromSweep)
	{
		DestroySelf();
	}
}
