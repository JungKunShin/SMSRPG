// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_Rskill.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/C_SkillSystemComponent.h"


UC_BTTask_Rskill::UC_BTTask_Rskill()
{

	bNotifyTick = true;
}

EBTNodeResult::Type UC_BTTask_Rskill::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	

	if (!SelfActor || !BBComp || !SelfActor->SkillSytemComponent)
	{
		return EBTNodeResult::Failed;
	}


	UAnimInstance* AnimInstance = SelfActor->GetMesh()->GetAnimInstance();

	
	if (AnimInstance->Montage_IsPlaying(nullptr))
	{
		bSkillStarted = false;
		return EBTNodeResult::InProgress;
	}

	// 아무것도 실행 중이 아니면 바로 시작
	SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->SkillQ);

	bSkillStarted = true;

	return EBTNodeResult::InProgress;




}

void UC_BTTask_Rskill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

		

		// 스킬 사용
		SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->SkillQ);


		bSkillStarted = true;
		return;

	}



	if (AnimInstance)
	{
		UAnimMontage* PlayingMontage = AnimInstance->GetCurrentActiveMontage();

		//  몽타주가 끝났을 때 조건
		if (!AnimInstance->Montage_IsPlaying(SelfActor->RSkillMontage) &&
			(PlayingMontage != SelfActor->RSkillMontage))
		{


			BBComp->SetValueAsBool(KeyOnRSkill.SelectedKeyName, false);
			BBComp->SetValueAsBool(KeyCanAttack.SelectedKeyName, true);
			// 몽타주가 종료되었음을 의미
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);


		}
	}





}
