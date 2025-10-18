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
		// 다른 몽타주가 재생 중이라면 대기
		if (AnimInstance->Montage_IsPlaying(nullptr))
			return;

		


	//	BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f); // 초기화
	

		// 스킬 사용
		SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->Skill1);

		

		bSkillStarted = true;
		return;

	}



	if (AnimInstance)
	{
		UAnimMontage* PlayingMontage = AnimInstance->GetCurrentActiveMontage();

		//  몽타주가 끝났을 때 조건
		if (!AnimInstance->Montage_IsPlaying(SelfActor->BaseAttackMontage) &&
			(PlayingMontage != SelfActor->BaseAttackMontage))
		{


			// 몽타주가 종료되었음을 의미
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);


		}
	}





}
