// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_QSkill.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/C_SkillSystemComponent.h"


UC_BTTask_QSkill::UC_BTTask_QSkill()
{

	bNotifyTick = true; // �� �ʿ�! ƽ Ÿ��ũ�� ����ϱ����ؼ�
}

EBTNodeResult::Type UC_BTTask_QSkill::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	

	if (!SelfActor || !BBComp || !SelfActor->SkillSytemComponent)
	{
		return EBTNodeResult::Failed;
	}
	// 1. ���� �ִϸ��̼� ���� Ȯ�� q skill ����Ҷ� ��Ÿ�����
	//UAnimInstance* Animinstance = SelfActor->GetMesh()->GetAnimInstance();

	//Animinstance->StopAllMontages(0.25f);


	/*
	if (Animinstance && Animinstance->Montage_IsPlaying(SelfActor->BaseAttackMontage))
	{
		return EBTNodeResult::Failed;
	}
	*/

	

    	bSkillStarted = false;

	    // �⺻���� �����ϰ� ��ų����ϱ�
	    BBComp->SetValueAsBool(KeyCanAttack.SelectedKeyName, false);


	    // ���� Ȯ�� ����� ���� - 40
	    //SelfActor->EnemyInfo.CurMp -= 40.f;
	  //  BBComp->SetValueAsFloat(KeyMana.SelectedKeyName, SelfActor->EnemyInfo.CurMp);

		// ��Ÿ�� �ʱ�ȭ 
		//BBComp->SetValueAsFloat(KeyQSkillCooldown.SelectedKeyName, 0.0f);

		// ��ų ���
	   // SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->Skill2);

		return EBTNodeResult::InProgress;
	
}



void UC_BTTask_QSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	if (!SelfActor || !SelfActor->QSkillMontage)
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

		// �ٸ� ��Ÿ�ְ� �������� �� Q��ų �ߵ�
		SelfActor->EnemyInfo.CurMp -= 40.f;
		BBComp->SetValueAsFloat(KeyMana.SelectedKeyName, SelfActor->EnemyInfo.CurMp);

		BBComp->SetValueAsFloat(KeyQSkillCooldown.SelectedKeyName, 0.0f);
		SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->Skill2);

		bSkillStarted = true;
		return;
	}




	if (AnimInstance && !AnimInstance->Montage_IsPlaying(SelfActor->QSkillMontage))
	{


		BBComp->SetValueAsBool(KeyOnQSkill.SelectedKeyName, false);
		BBComp->SetValueAsBool(KeyCanAttack.SelectedKeyName, true);


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // ��Ÿ�� ������ �� ���� ó��
	}

}
