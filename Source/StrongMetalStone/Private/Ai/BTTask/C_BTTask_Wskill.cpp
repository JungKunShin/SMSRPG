// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_Wskill.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/C_SkillSystemComponent.h"


UC_BTTask_Wskill::UC_BTTask_Wskill()
{

	bNotifyTick = true; // 꼭 필요! 틱 타스크를 사용하기위해서

}

EBTNodeResult::Type UC_BTTask_Wskill::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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



void UC_BTTask_Wskill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{


	if (!SelfActor || !SelfActor->WSkillMontage)
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

		// 마나 확인 사용후 마나 - 60
		SelfActor->EnemyInfo.CurMp -= 60.f;
		BBComp->SetValueAsFloat(KeyMana.SelectedKeyName, SelfActor->EnemyInfo.CurMp);

		// 쿨타임 초기화 
		BBComp->SetValueAsFloat(KeyWSkillCooldown.SelectedKeyName, 0.0f);


		// 스킬 사용
		SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->Skill3);


		bSkillStarted = true;
		return;
	}

	if (AnimInstance)
	{
		UAnimMontage* PlayingMontage = AnimInstance->GetCurrentActiveMontage();

		//  몽타주가 끝났을 때 조건
		if (!AnimInstance->Montage_IsPlaying(SelfActor->WSkillMontage) &&
			(PlayingMontage != SelfActor->WSkillMontage))
		{
			
			BBComp->SetValueAsBool(KeyOnWSkill.SelectedKeyName, false);
			BBComp->SetValueAsBool(KeybCanAttack.SelectedKeyName, true);
			// 몽타주가 종료되었음을 의미
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}


}
