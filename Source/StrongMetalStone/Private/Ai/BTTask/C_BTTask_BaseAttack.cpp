// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_BaseAttack.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/C_SkillSystemComponent.h"


EBTNodeResult::Type UC_BTTask_BaseAttack::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


	UAnimInstance* Animinstance = SelfActor->GetMesh()->GetAnimInstance();
	if (Animinstance && Animinstance->Montage_IsPlaying(SelfActor->BaseAttackMontage))
	{
		return EBTNodeResult::Failed;
	}
	


	// �⺻ ���� ��ų ���
	SelfActor->SkillSytemComponent->PlaySkill(SelfActor->SkillSytemComponent->Skill1);
		


	// �⺻���ݽ� ���� +5
	SelfActor->EnemyInfo.CurMp = FMath::Min(SelfActor->EnemyInfo.CurMp + 20.0f, SelfActor->EnemyInfo.MaxMp);

	BBComp->SetValueAsFloat(KeyMana.SelectedKeyName, SelfActor->EnemyInfo.CurMp);




	// �⺻���� 4Ÿ
	int32 AttackCount = BBComp->GetValueAsInt(KeyAttackCount.SelectedKeyName);

	BBComp->SetValueAsInt(KeyAttackCount.SelectedKeyName, AttackCount + 1);

	if (AttackCount >= 3)
	{
		BBComp->SetValueAsBool(KeyOnFinishAttack.SelectedKeyName, true);

		BBComp->SetValueAsInt(KeyAttackCount.SelectedKeyName, 0);

	}



	return EBTNodeResult::Succeeded;



}
