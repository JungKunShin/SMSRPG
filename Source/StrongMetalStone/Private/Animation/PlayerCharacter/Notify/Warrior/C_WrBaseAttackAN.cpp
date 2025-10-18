// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Warrior/C_WrBaseAttackAN.h"
#include "Character/C_Warrior.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_WrBaseAttackAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	
	if (!MeshComp)return;

	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());//PlayerCharacter로 형변환
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;

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

	if (Warrior->HasAuthority() ) // 서버에서만
	{
		FVector ForwardVector = Warrior->GetActorForwardVector(); // 전사 앞방향 저장
		FVector SpawnLocation = Warrior->GetActorLocation() + ForwardVector * 100.0f; // 전사 위치에서 앞방향으로 1미터
		FRotator SpawnRotation = Warrior->GetActorRotation(); // 전사 각도 저장

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Warrior;
		SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_WrBaseAttackAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // 액터 소환
	}
}
