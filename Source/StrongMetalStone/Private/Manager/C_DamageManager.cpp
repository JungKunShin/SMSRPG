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

	//�� ������ ����ó��

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
	//�����̻�
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
		Origin,        // ������ �߽� ��ġ
		DamageRadius,           // ������ ������
		TArray<TEnumAsByte<EObjectTypeQuery>>{UEngineTypes::ConvertToObjectType(ECC_Pawn)}, // ã���� �ϴ� ��ü Ÿ�� (EnemyAttackŸ������ �ٲ���ϴµ� �����غ��� Ȯ���ҰͰ��Ƽ� �ϴ� ���� �ٲ���)
		nullptr,                // Ư�� Ŭ������ ã�� �� (null�̸� ��� ����)
		IgnoreActors,  // ������ ���� (�ڱ� �ڽ� ��)
		OverlappedActors        // ����� ���� �迭
	);

	UGameplayStatics::ApplyRadialDamage( //���� �������� �ִ� �Լ� �������� ���� ��ü���� TakeDamage�� ȣ���
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

	//�����̻�
	if (!EffectClass) return;
	for (AActor* Actor : OverlappedActors)
	{
		CastWCharacter(Actor)->MultiTakeEffect(EffectClass);
	}

	//UI���Ž����ִ� �Լ� ������
}
