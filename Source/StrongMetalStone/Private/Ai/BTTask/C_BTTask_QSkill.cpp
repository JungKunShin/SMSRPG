// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_QSkill.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/C_SkillSystemComponent.h"


UC_BTTask_QSkill::UC_BTTask_QSkill()
{

	bNotifyTick = true; // 꼭 필요! 틱 타스크를 사용하기위해서
}

EBTNodeResult::Type UC_BTTask_QSkill::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	

	if (!SelfActor || !BBComp || !SelfActor->SkillSytemComponent)
	{
		return EBTNodeResult::Failed;
	}
	// 1. 현재 애니메이션 상태 확인 q skill 사용할때 몽타주취소
	//UAnimInstance* Animinstance = SelfActor->GetMesh()->GetAnimInstance();

	//Animinstance->StopAllMontages(0.25f);


	/*
	if (Animinstance && Animinstance->Montage_IsPlaying(SelfActor->BaseAttackMontage))
	{
		return EBTNodeResult::Failed;
	}
	*/

	

    	bSkillStarted = false;

	    // 기본공격 차단하고 스킬사용하기
	    BBComp->SetValueAsBool(KeyCanAttack.SelectedKeyName, false);


	    // 마나 확인 사용후 마나 - 40
	    //SelfActor->EnemyInfo.CurMp -= 40.f;
	  //  BBComp->SetValueAsFloat(KeyMana.SelectedKeyName, SelfActor->EnemyInfo.CurMp);

		// 쿨타임 초기화 
		//BBComp->SetValueAsFloat(KeyQSkillCooldown.SelectedKeyName, 0.0f);

		// 스킬 사용
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
		// 다른 몽타주가 재생 중이라면 대기
		if (AnimInstance->Montage_IsPlaying(nullptr))
			return;

		// 다른 몽타주가 끝났으면 → Q스킬 발동
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


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // 몽타주 끝났을 때 성공 처리
	}

}
