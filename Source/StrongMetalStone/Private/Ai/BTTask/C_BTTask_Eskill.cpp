// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_Eskill.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/C_SkillSystemComponent.h"


UC_BTTask_Eskill::UC_BTTask_Eskill()
{
	bNotifyTick = true; // 꼭 필요! 틱 타스크를 사용하기위해서
}


EBTNodeResult::Type UC_BTTask_Eskill::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{



	if (!SelfActor || !BBComp || !SelfActor->SkillSytemComponent)
	{ 
		return EBTNodeResult::Failed;
    }


	bSkillStarted = false;

	// 기본공격 차단하고 스킬사용하기
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
		// 다른 몽타주가 재생 중이라면 대기
		if (AnimInstance->Montage_IsPlaying(nullptr))
			return;

		// 마나 확인 사용후 마나 - 80
		SelfActor->EnemyInfo.CurMp -= 80.f;
		BBComp->SetValueAsFloat(KeyMana.SelectedKeyName, SelfActor->EnemyInfo.CurMp);


		// 쿨타임 초기화 
		BBComp->SetValueAsFloat(KeyESkillCooldown.SelectedKeyName, 0.0f);

		// 스킬 사용
		SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->Skill4);


		bSkillStarted = true;
		return;
	}



	if (AnimInstance)
	{
		UAnimMontage* PlayingMontage = AnimInstance->GetCurrentActiveMontage();

		     //  몽타주가 끝났을 때 조건
		if (!AnimInstance->Montage_IsPlaying(SelfActor->ESkillMontage) &&
			(PlayingMontage != SelfActor->ESkillMontage))
		{


			BBComp->SetValueAsBool(KeyOnESkill.SelectedKeyName, false);
			BBComp->SetValueAsBool(KeybCanAttack.SelectedKeyName, true);
			// 몽타주가 종료되었음을 의미
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);


		}
	}



}
