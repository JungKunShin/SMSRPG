// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Mage/C_MgPlasmaDescentAN.h"
#include "Character/C_Mage.h"

void UC_MgPlasmaDescentAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;


	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());//PlayerCharacter로 형변환
	if (!Mage)return;

	// 데미지 두번 들어가는것 방지 코드
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	static TMap<TWeakObjectPtr<AActor>, float> LastNotifyTimes;
	const float CurrentTime = MeshComp->GetWorld()->GetTimeSeconds();

	constexpr float MinInterval = 0.05f; // 같은 프레임 내 중복 방지
	if (LastNotifyTimes.Contains(Owner))
	{
		float LastTime = LastNotifyTimes[Owner];
		if (CurrentTime - LastTime < MinInterval)
		{
			// 너무 짧은 시간 내 두 번 들어오면 무시
			return;
		}
	}

	LastNotifyTimes.Add(Owner, CurrentTime);
	//
	if (Mage->HasAuthority()) // 서버에서만
	{
		FVector ForwardVector = Mage->GetActorForwardVector(); // 전사 앞방향 저장
		FVector SpawnLocation = Mage->GetActorLocation() + ForwardVector * FORWARD_DISTANCE +FVector(0.0f,0.0f,DOWN_HEIGHT); // 전사 위치에서 앞방향으로 7미터+조금 아래 생성
		FRotator SpawnRotation = Mage->GetActorRotation(); // 전사 각도 저장

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Mage;
		SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_MgPlasmaDescentAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // 액터 소환
	}
}
