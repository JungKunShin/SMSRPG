// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/C_ComboResetAN.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_ComboResetAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;

	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Character->GetController());
	if (!WPC)return;

	// ������ �ι� ���°� ���� �ڵ�
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	static TMap<TWeakObjectPtr<AActor>, float> LastNotifyTimes;
	const float CurrentTime = MeshComp->GetWorld()->GetTimeSeconds();

	constexpr float MinInterval = 0.05f; // ���� ������ �� �ߺ� ����
	if (LastNotifyTimes.Contains(Owner))
	{
		float LastTime = LastNotifyTimes[Owner];
		if (CurrentTime - LastTime < MinInterval)
		{
			// �ʹ� ª�� �ð� �� �� �� ������ ����
			return;
		}
	}

	LastNotifyTimes.Add(Owner, CurrentTime);
	//
	if (Character->SkillSytemComponent->CurSkill)
	{
		Character->SkillSytemComponent->CurSkill->SkillCombo = 0; // ��ų �޺� �ʱ�ȭ
		Character->SkillSytemComponent->Attack->SkillCombo = 0;
		Character->SkillSytemComponent->Skill1->SkillCombo = 0;
		Character->SkillSytemComponent->Skill2->SkillCombo = 0;
		Character->SkillSytemComponent->Skill3->SkillCombo = 0;
		Character->SkillSytemComponent->Skill4->SkillCombo = 0;
		Character->SkillSytemComponent->SkillQ->SkillCombo = 0;
		Character->SkillSytemComponent->SkillE->SkillCombo = 0;

	}
}
