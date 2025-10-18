// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/Minion/C_BTTask_Minion_Toilet_Attack.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/C_SkillSystemComponent.h"

UC_BTTask_Minion_Toilet_Attack::UC_BTTask_Minion_Toilet_Attack()
{

	bNotifyTick = true;

}

EBTNodeResult::Type UC_BTTask_Minion_Toilet_Attack::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!SelfActor || !BBComp || !SelfActor->SkillSytemComponent)
	{
		return EBTNodeResult::Failed;
	}


	bSkillStarted = false;



	return EBTNodeResult::InProgress;

}


void UC_BTTask_Minion_Toilet_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{



	if (!SelfActor || !SelfActor->BaseAttackMontage)
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

		


	//	BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f); // �ʱ�ȭ
	

		// ��ų ���
		SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->Skill1);

		

		bSkillStarted = true;
		return;

	}



	if (AnimInstance)
	{
		UAnimMontage* PlayingMontage = AnimInstance->GetCurrentActiveMontage();

		//  ��Ÿ�ְ� ������ �� ����
		if (!AnimInstance->Montage_IsPlaying(SelfActor->BaseAttackMontage) &&
			(PlayingMontage != SelfActor->BaseAttackMontage))
		{


			// ��Ÿ�ְ� ����Ǿ����� �ǹ�
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);


		}
	}





}
