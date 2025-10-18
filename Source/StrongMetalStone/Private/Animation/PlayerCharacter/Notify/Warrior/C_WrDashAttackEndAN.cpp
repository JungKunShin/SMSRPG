// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Warrior/C_WrDashAttackEndAN.h"
#include "Character/C_Warrior.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_WrDashAttackEndAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;

	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
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
	if (Warrior->HasAuthority())
	{
		FVector ForwardVector = Warrior->GetActorForwardVector(); // 전사 앞방향 저장
		FVector SpawnLocation = MeshComp->GetSocketLocation("FX_Sword_Top")+ForwardVector *200.0f; // 전사 검 끝 소켓 위치에서 앞방향으로 2미터
		FRotator SpawnRotation = MeshComp->GetSocketRotation("FX_Sword_Top"); // 전사 검 끝 소켓 각도 저장
		
		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Warrior;
		SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_WrDashAttackAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // 액터 소환
	}
}
