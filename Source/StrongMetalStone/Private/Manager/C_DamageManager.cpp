// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/C_DamageManager.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Enemy.h"
#include "Character/Riding/C_SMSRiding.h"
#include "Effect/C_SMSEffectINS.h"
#include "FrameWork.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "Engine/DamageEvents.h"

void UC_DamageManager::ApplyPointDamage(AActor* TargetActor, AActor* DamageActor, float Damage, const FHitResult& Hit, TSubclassOf<AC_SMSEffectINS> EffectClass, AController* InstigatedBy, FVector ShotDirection)
{
	if (!TargetActor) return;

	if (ShotDirection != FVector(0, 0, 0))
		ShotDirection = (TargetActor->GetActorLocation() - DamageActor->GetActorLocation()).GetSafeNormal();

	if (InstigatedBy == nullptr)
		InstigatedBy = DamageActor->GetMyPC();

	//위 까지는 예외처리

	FPointDamageEvent DamageEvent;
	DamageEvent.Damage = Damage;
	DamageEvent.HitInfo = Hit;
	DamageEvent.ShotDirection = ShotDirection;
	DamageEvent.DamageTypeClass = UDamageType::StaticClass();

	if (Cast<AC_PlayerCharacter>(TargetActor))
	{
		if (Cast<AC_PlayerCharacter>(TargetActor)->CharacterInfo.Curhp <= 0)
		{
			return;
		}
	}
	else if (Cast<AC_Enemy>(TargetActor))
	{
		if (Cast<AC_Enemy>(TargetActor)->EnemyInfo.Curhp <= 0)
		{
			return;
		}
	}
	else if (Cast<AC_SMSRiding>(TargetActor))
	{
		TargetActor = Cast<AC_SMSRiding>(TargetActor)->CurrentRider;
	}
	
	UGameplayStatics::ApplyDamage(TargetActor, Damage, InstigatedBy, DamageActor, UDamageType::StaticClass());	
	//상태이상
	if (EffectClass)
	{
		Cast<AC_SMSCharacter>(TargetActor)->MultiTakeEffect(EffectClass);
	}
		

	

}

void UC_DamageManager::ApplyRadialDamage(AActor* DamageActor, float Damage, const FVector& Origin, float DamageRadius, TArray<AActor*> IgnoreActors, TSubclassOf<AC_SMSEffectINS> EffectClass, AController* InstigatedBy, bool bDoFullDamage)
{
	IgnoreActors.Add(DamageActor);

	TArray<AActor*> OverlappedActors;
	UKismetSystemLibrary::SphereOverlapActors(
		DamageActor->GetWorld(),
		Origin,        // 범위의 중심 위치
		DamageRadius,           // 범위의 반지름
		TArray<TEnumAsByte<EObjectTypeQuery>>{UEngineTypes::ConvertToObjectType(ECC_Pawn)}, // 찾고자 하는 객체 타입 (EnemyAttack타입으로 바꿔야하는데 실험해봐야 확실할것같아서 일단 냅둠 바꿔조)
		nullptr,                // 특정 클래스만 찾을 때 (null이면 모든 액터)
		IgnoreActors,  // 무시할 액터 (자기 자신 등)
		OverlappedActors        // 결과를 담을 배열
	);

	UGameplayStatics::ApplyRadialDamage( //실제 데미지를 주는 함수 데미지를 받은 객체들이 TakeDamage가 호출됨
		DamageActor->GetWorld(),
		Damage,
		Origin,
		DamageRadius,
		UDamageType::StaticClass(),
		IgnoreActors,
		DamageActor,
		InstigatedBy,
		bDoFullDamage
	);

	//상태이상
	if (!EffectClass) return;
	for (AActor* Actor : OverlappedActors)
	{
		CastWCharacter(Actor)->MultiTakeEffect(EffectClass);
	}

	//UI갱신시켜주는 함수 들어갈예정
}
