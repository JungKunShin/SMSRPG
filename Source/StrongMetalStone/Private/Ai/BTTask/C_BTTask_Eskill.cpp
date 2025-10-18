// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_Eskill.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/C_SkillSystemComponent.h"


UC_BTTask_Eskill::UC_BTTask_Eskill()
{
	bNotifyTick = true; // �� �ʿ�! ƽ Ÿ��ũ�� ����ϱ����ؼ�
}


EBTNodeResult::Type UC_BTTask_Eskill::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{



	if (!SelfActor || !BBComp || !SelfActor->SkillSytemComponent)
	{ 
		return EBTNodeResult::Failed;
    }


	bSkillStarted = false;

	// �⺻���� �����ϰ� ��ų����ϱ�
	BBComp->SetValueAsBool(KeybCanAttack.SelectedKeyName, false);
	
	

	return EBTNodeResult::InProgress;





}

void UC_BTTask_Eskill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{



	if (!SelfActor || !SelfActor->ESkillMontage)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}


	UAnimInstance* AnimInstance = SelfActor->GetMesh()->GetAnimInstance();



	if (!bSkillStarted)
	{
		// �ٸ� ��Ÿ�ְ� ��� ���̶�� ���
		if (AnimInstance->Montage_IsPlaying(nullptr))
			return;

		// ���� Ȯ�� ����� ���� - 80
		SelfActor->EnemyInfo.CurMp -= 80.f;
		BBComp->SetValueAsFloat(KeyMana.SelectedKeyName, SelfActor->EnemyInfo.CurMp);


		// ��Ÿ�� �ʱ�ȭ 
		BBComp->SetValueAsFloat(KeyESkillCooldown.SelectedKeyName, 0.0f);

		// ��ų ���
		SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->Skill4);


		bSkillStarted = true;
		return;
	}



	if (AnimInstance)
	{
		UAnimMontage* PlayingMontage = AnimInstance->GetCurrentActiveMontage();

		     //  ��Ÿ�ְ� ������ �� ����
		if (!AnimInstance->Montage_IsPlaying(SelfActor->ESkillMontage) &&
			(PlayingMontage != SelfActor->ESkillMontage))
		{


			BBComp->SetValueAsBool(KeyOnESkill.SelectedKeyName, false);
			BBComp->SetValueAsBool(KeybCanAttack.SelectedKeyName, true);
			// ��Ÿ�ְ� ����Ǿ����� �ǹ�
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);


		}
	}



}
