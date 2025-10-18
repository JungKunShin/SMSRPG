// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_Dodge.h"
#include "Character/C_RevenantBossCharacter.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Character/C_Enemy.h"
#include "Component/C_SkillSystemComponent.h"

#include "BehaviorTree/BlackboardComponent.h"


UC_BTTask_Dodge::UC_BTTask_Dodge()
{

	bNotifyTick = true;
	bSkillStarted = false;
	bCreateNodeInstance = true;

}

EBTNodeResult::Type UC_BTTask_Dodge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!SelfActor || !BBComp || !SelfActor->SkillSytemComponent)
	{
		return EBTNodeResult::Failed;
	}



	bSkillStarted = false;

	// 기본공격 차단하고 스킬사용하기
	BBComp->SetValueAsBool(KeyCanAttack.SelectedKeyName, false);


	return EBTNodeResult::InProgress;

}

void UC_BTTask_Dodge::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{



	if (!SelfActor || !SelfActor->DodgeMontage)
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

		
		
		

		BBComp->SetValueAsFloat(KeyDodgeSkillCooldown.SelectedKeyName, 0.0f);

		SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->Dash);

		bSkillStarted = true;
		return;
	}




	if (AnimInstance && !AnimInstance->Montage_IsPlaying(SelfActor->DodgeMontage))
	{


		BBComp->SetValueAsBool(KeyOnDodgeSkill.SelectedKeyName, false);
		BBComp->SetValueAsBool(KeyCanAttack.SelectedKeyName, true);


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); // 몽타주 끝났을 때 성공 처리
	}

}
