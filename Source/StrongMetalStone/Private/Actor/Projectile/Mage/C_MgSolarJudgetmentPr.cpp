// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/Mage/C_MgSolarJudgetmentPr.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include"Components/DecalComponent.h"

AC_MgSolarJudgetmentPr::AC_MgSolarJudgetmentPr()
{
	Damage = 20.0f; // 데미지 5.0
	DelayTime = 3.0f; // AP 파괴 시간
	ShakeDegree = 8.0f;

	ProjectileMovement->InitialSpeed = 1000.0f;
	ProjectileMovement->MaxSpeed = 1000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bShouldBounce = false;
}

void AC_MgSolarJudgetmentPr::BeginPlay()
{
	Super::BeginPlay();
	Damage *= Owner->CharacterInfo.Damage;
	AttackDecal();
}

void AC_MgSolarJudgetmentPr::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit with: %s"), *OtherActor->GetName());
	SpawnedDecal->Destroy();
	Super::OnAttackOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AC_MgSolarJudgetmentPr::AttackDecal()
{
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * 12000.0f) + FVector(0.0f, 0.0f, -700.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByProfile(HitResult, Start, End, FName("BlockAll"), Params);

	if (bHit)
	{
		SpawnedDecal = GetWorld()->SpawnActor<AC_DecalAP>(DecalClass, HitResult.Location, GetActorRotation());
	}
}
