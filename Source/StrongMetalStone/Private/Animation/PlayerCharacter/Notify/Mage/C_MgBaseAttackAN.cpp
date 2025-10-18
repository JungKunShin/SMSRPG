// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Mage/C_MgBaseAttackAN.h"
#include "Character/C_Mage.h"

void UC_MgBaseAttackAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;


	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());//PlayerCharacter로 형변환
	if (!Mage)return;
	
	if (!Mage->SkillSytemComponent->CurSkill)return;

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
	if (Mage->HasAuthority())
	{
		FVector ForwardVector = Mage->GetActorForwardVector(); // 마법사 앞방향 저장
		FRotator SpawnRotation = Mage->GetActorRotation(); // 전사 각도 저장
		FVector SpawnLocation= MeshComp->GetSocketLocation("FX_Hand_R4") + ForwardVector * SPAWNED_DISTANCE;
		if (Mage->SkillSytemComponent->CurSkill->SkillCombo == 2)
		{
			SpawnLocation = MeshComp->GetSocketLocation("FX_Hand_L4") + ForwardVector * SPAWNED_DISTANCE;
		}
		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Mage;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnedProjectile = MeshComp->GetWorld()->SpawnActor<AC_MgBaseAttackPr>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParam); // 액터 소환
	}
}
