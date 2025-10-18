// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/Minion/C_BTTask_MinionSkill1.h"
#include "Character/C_Enemy.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Character/C_Minion.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BTTask_MinionSkill1::UC_BTTask_MinionSkill1()
{
	bNotifyTick = true;
	bAttackStarted = false;
	bCreateNodeInstance = true;

}

EBTNodeResult::Type UC_BTTask_MinionSkill1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedOwnerComp = &OwnerComp;

	SelfActor = GetEnemyCharacterSkill1(OwnerComp);
	if (!SelfActor || !SelfActor->QSkillMontage)
	{
		return EBTNodeResult::Failed;
	}

	UAnimInstance* AnimInstance = SelfActor->GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return EBTNodeResult::Failed;
	}

	AnimInstance->OnMontageEnded.RemoveDynamic(this, &UC_BTTask_MinionSkill1::OnMontageEnded);
	AnimInstance->OnMontageEnded.AddDynamic(this, &UC_BTTask_MinionSkill1::OnMontageEnded);

	//AnimInstance->Montage_Play(SelfActor->QSkillMontage);

	SelfActor->MultiPlayMontage(SelfActor->QSkillMontage);

	SelfActor->SuperArmor = true;

	bAttackStarted = true;

	return EBTNodeResult::InProgress;

}

void UC_BTTask_MinionSkill1::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!SelfActor || !SelfActor->QSkillMontage)
	{
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
	}
}

AC_Enemy* UC_BTTask_MinionSkill1::GetEnemyCharacterSkill1(UBehaviorTreeComponent& OwnerComp)
{
	return Cast<AC_Enemy>(OwnerComp.GetAIOwner()->GetPawn());
}

void UC_BTTask_MinionSkill1::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

	if (!SelfActor || Montage != SelfActor->QSkillMontage)
		return;

	UAnimInstance* AnimInstance = SelfActor->GetMesh()->GetAnimInstance();

	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &UC_BTTask_MinionSkill1::OnMontageEnded);


	}

	if (CachedOwnerComp)
	{
		UBlackboardComponent* BBComp1 = CachedOwnerComp->GetBlackboardComponent();
		if (BBComp1)
		{
			// 쿨타임 초기화
			BBComp1->SetValueAsFloat(KeySkillCoolTime.SelectedKeyName, 0.0f);
			BBComp1->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f);
			BBComp1->SetValueAsBool(KeyOnSkill.SelectedKeyName, false);

		}
	}

	SelfActor->SuperArmor = false;

	FinishLatentTask(*CachedOwnerComp, bInterrupted ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);
}
