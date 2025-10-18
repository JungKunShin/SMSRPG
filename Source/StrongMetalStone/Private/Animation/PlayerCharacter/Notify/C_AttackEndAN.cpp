// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/C_AttackEndAN.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_AttackEndAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;

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
	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Character->GetController());
	if (!WPC)return;

	if (Character->SkillSytemComponent->CurSkill)
	{
		Character->SkillSytemComponent->CurSkill->SkillCombo = 0; // 현재 스킬의 스킬콤보 초기화
	}
}
