// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Undead_CountAttack_AN.h"
#include "Character/C_Undead.h"
#include "Character/C_PlayerCharacter.h"

void UC_Undead_CountAttack_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{



	AC_Undead* Undead = Cast<AC_Undead>(MeshComp->GetOwner());

	if (!Undead)return;


	// 서버인지 체크 
	if (!Undead->HasAuthority())
	{
		return;
	}


	// 해당 노티파이의 오너가 피가 1이상인지 체크
	if (Undead->EnemyInfo.Curhp <= 0.0f) return;



	// 반격기가 정상적으로 종료된다면 
	if (!Undead->bParryFinishedClean) return;





	// 반원에 대한 플레이어를 감지하고 데미지 처리하기

	FVector ToiletLocation = Undead->GetMesh()->GetSocketLocation(SocketName);
	float Radius = 600.0f;

	// 플레이어
	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);

	// 자기자신
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Undead);

	// 오버랩 수행
	bool bHit = UKismetSystemLibrary::SphereOverlapActors
	(
		Undead->GetWorld(),
		ToiletLocation,                 // 중점 위치
		Radius,                      // 범위
		ObjectTypes,                // 오브젝트타입
		ACharacter::StaticClass(), // Actor Class Filter
		ActorsToIgnore,           // 무시할엑터들
		OverlappedActors         // 오버랩된 엑터들
	);

	if (!bHit) return;

	DrawDebugSphere(Undead->GetWorld(), ToiletLocation, Radius, 16, FColor::Red, false, 1.0f);

	for (AActor* Actor : OverlappedActors)
	{
		AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(Actor);
		if (!Player) continue;



		FHitResult HitResult;
		//                                 피해자 ,가해자 ,데미지양 ,그냥히트결과, 상태이상효과,
		UC_DamageManager::ApplyPointDamage(Player, Undead, Undead->BlockAccumulatedDamage, HitResult);

		Player->PlayCameraShake2(Undead->CamShakeClass);

	}


	Undead->BlockAccumulatedDamage = 0.0f;
	Undead->bParryFinishedClean = false;



}
