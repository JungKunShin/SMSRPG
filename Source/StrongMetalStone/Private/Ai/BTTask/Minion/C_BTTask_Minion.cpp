// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/Minion/C_BTTask_Minion.h"
#include "Character/C_Enemy.h"
#include "Animation/AnimInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UC_BTTask_Minion::UC_BTTask_Minion()
{
	bNotifyTick = true;
	bAttackStarted = false;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UC_BTTask_Minion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	CachedOwnerComp = &OwnerComp;

	SelfActor = GetEnemyCharacter(OwnerComp);
	if (!SelfActor || !SelfActor->BaseAttackMontage)
	{
		return EBTNodeResult::Failed;
	}

	UAnimInstance* AnimInstance = SelfActor->GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return EBTNodeResult::Failed;
	}

	AnimInstance->OnMontageEnded.RemoveDynamic(this, &UC_BTTask_Minion::OnMontageEnded);
	AnimInstance->OnMontageEnded.AddDynamic(this, &UC_BTTask_Minion::OnMontageEnded);

	//AnimInstance->Montage_Play(SelfActor->QSkillMontage);

	SelfActor->MultiPlayMontage(SelfActor->BaseAttackMontage);


	// 타겟 어그로 : 기본공격시 어그로 시간 초기화
	if (CachedOwnerComp)
	{
		UBlackboardComponent* BBComp2 = CachedOwnerComp->GetBlackboardComponent();
		if (BBComp2)
		{
			// 쿨타임 초기화
			BBComp2->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f);
		}
	}




	bAttackStarted = true;

	return EBTNodeResult::InProgress;

}

void UC_BTTask_Minion::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (!SelfActor || !SelfActor->BaseAttackMontage)
	{
		FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
	}
}

AC_Enemy* UC_BTTask_Minion::GetEnemyCharacter(UBehaviorTreeComponent& OwnerComp)
{
	return Cast<AC_Enemy>(OwnerComp.GetAIOwner()->GetPawn());
}

void UC_BTTask_Minion::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{

	if (!SelfActor || Montage != SelfActor->BaseAttackMontage)
		return;

	UAnimInstance* AnimInstance = SelfActor->GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &UC_BTTask_Minion::OnMontageEnded);
	}

	FinishLatentTask(*CachedOwnerComp, bInterrupted ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);
}
