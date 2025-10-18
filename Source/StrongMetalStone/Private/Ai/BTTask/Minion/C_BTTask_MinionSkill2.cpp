// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/Minion/C_BTTask_MinionSkill2.h"
#include "Character/C_Enemy.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Character/C_Minion.h"
#include "BehaviorTree/BlackboardComponent.h"



UC_BTTask_MinionSkill2::UC_BTTask_MinionSkill2()
{

	bNotifyTick = true;
	bAttackStarted = false;
	bCreateNodeInstance = true;

}

EBTNodeResult::Type UC_BTTask_MinionSkill2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	

	CachedOwnerComp = &OwnerComp;

	SelfActor = GetEnemyCharacterSkill2(OwnerComp);

	if (!SelfActor || !SelfActor->WSkillMontage)
	{
		return EBTNodeResult::Failed;
	}

	UAnimInstance* AnimInstance = SelfActor->GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return EBTNodeResult::Failed;
	}

	AnimInstance->OnMontageEnded.RemoveDynamic(this, &UC_BTTask_MinionSkill2::OnMontageEnded);
	AnimInstance->OnMontageEnded.AddDynamic(this, &UC_BTTask_MinionSkill2::OnMontageEnded);



	SelfActor->MultiPlayMontage(SelfActor->WSkillMontage);

	SelfActor->SuperArmor = true;

	bAttackStarted = true;

	return EBTNodeResult::InProgress;



}

void UC_BTTask_MinionSkill2::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	if (!SelfActor || !SelfActor->WSkillMontage)
	{
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
	}


}

AC_Enemy* UC_BTTask_MinionSkill2::GetEnemyCharacterSkill2(UBehaviorTreeComponent& OwnerComp)
{

	return Cast<AC_Enemy>(OwnerComp.GetAIOwner()->GetPawn());

}

void UC_BTTask_MinionSkill2::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

	if (!SelfActor || Montage != SelfActor->WSkillMontage)
		return;

	UAnimInstance* AnimInstance = SelfActor->GetMesh()->GetAnimInstance();

	if (AnimInstance)
	{

		AnimInstance->OnMontageEnded.RemoveDynamic(this, &UC_BTTask_MinionSkill2::OnMontageEnded);

	}

	if (CachedOwnerComp)
	{
		UBlackboardComponent* BBComp1 = CachedOwnerComp->GetBlackboardComponent();
		if (BBComp1)
		{
			// 스킬 쿨타임 초기화
			BBComp1->SetValueAsFloat(KeySkillCoolTime2.SelectedKeyName, 0.0f);
			// 어그로 초기화
			BBComp1->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f);
			
			BBComp1->SetValueAsBool(KeyOnSkill2.SelectedKeyName, false);
		

		}
	}

	SelfActor->SuperArmor = false;

	FinishLatentTask(*CachedOwnerComp, bInterrupted ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);


}
