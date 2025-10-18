// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/Mage/C_MgBaseAttackPr.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/C_PlayerCharacter.h"
#include"Components/SphereComponent.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_MgBaseAttackPr::AC_MgBaseAttackPr()
{
	Damage = 1.0f; // 데미지 3.0
	DelayTime = 3.0f; // AP 파괴 시간
	ShakeDegree = 0.1f;

	ProjectileMovement->InitialSpeed = 4000.0f;
	ProjectileMovement->MaxSpeed = 4000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bShouldBounce = false;

}

void AC_MgBaseAttackPr::BeginPlay()
{
	Super::BeginPlay();

	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Owner->GetController());
	if (!WPC)return;
	if (!Owner->SkillSytemComponent->CurSkill) return;

	if (WPC->Subsystem && Owner->SkillSytemComponent->CurSkill->SkillCombo == 1) // 기본공격 콤보가 1이라면
	{
		Damage *= Owner->CharacterInfo.Damage ;
	}
	else if (WPC->Subsystem && Owner->SkillSytemComponent->CurSkill->SkillCombo == 2) // 기본공격 콤보가 2이라면
	{
		Damage *= Owner->CharacterInfo.Damage ;
	}
}

void AC_MgBaseAttackPr::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnAttackOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (bFromSweep)
	{
		DestroySelf();
	}
}
