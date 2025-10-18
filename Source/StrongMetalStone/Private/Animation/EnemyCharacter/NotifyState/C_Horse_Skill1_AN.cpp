// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Horse_Skill1_AN.h"
#include "Character/C_UndeadHorse.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UC_Horse_Skill1_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{



	AC_UndeadHorse* UndeadHorse = Cast<AC_UndeadHorse>(MeshComp->GetOwner());

	if (!UndeadHorse)return;


	// 서버인지 체크 
	if (!UndeadHorse->HasAuthority())
	{
		return;
	}


	// 해당 노티파이의 오너가 피가 1이상인지 체크
	if (UndeadHorse->EnemyInfo.Curhp <= 0.0f) return;



	// 반원에 대한 플레이어를 감지하고 데미지 처리하기

	FVector ToiletLocation = UndeadHorse->GetMesh()->GetSocketLocation(SocketName);
	float Radius = 300.0f;

	// 플레이어
	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);

	// 자기자신
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(UndeadHorse);

	// 오버랩 수행
	bool bHit = UKismetSystemLibrary::SphereOverlapActors
	(
		UndeadHorse->GetWorld(),
		ToiletLocation,                 // 중점 위치
		Radius,                      // 범위
		ObjectTypes,                // 오브젝트타입
		ACharacter::StaticClass(), // Actor Class Filter
		ActorsToIgnore,           // 무시할엑터들
		OverlappedActors         // 오버랩된 엑터들
	);

	if (!bHit) return;

	DrawDebugSphere(UndeadHorse->GetWorld(), ToiletLocation, Radius, 16, FColor::Red, false, 1.0f);

	for (AActor* Actor : OverlappedActors)
	{
		AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(Actor);
		if (!Player) return;



		FHitResult HitResult;
		//                                 피해자 ,가해자 ,데미지양 ,그냥히트결과, 상태이상효과,
		UC_DamageManager::ApplyPointDamage(Player, UndeadHorse, UndeadHorse->EnemyInfo.Damage, HitResult);



		// 중력 약화
		Player->GetCharacterMovement()->GravityScale = 0.4f;


		FVector ForwardDirection = -UndeadHorse->GetActorForwardVector();
		FVector LaunchVelocity = ForwardDirection * 1000.f + FVector(0, 0, 400.f); // 위로도 살짝 띄움

		Player->LaunchCharacter(LaunchVelocity, true, true);

		

		FTimerHandle GravityResetHandle;
		GetWorld()->GetTimerManager().SetTimer(GravityResetHandle, [=]()
			{
				Player->GetCharacterMovement()->GravityScale = 1.0f;
			}, 1.0f, false);  // 2초 뒤 원래대로


	}


}
