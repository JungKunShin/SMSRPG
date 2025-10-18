// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_Die.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Component/C_SkillSystemComponent.h"
#include "Ai/C_BossRevenantAiController.h"

EBTNodeResult::Type UC_BTTask_Die::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	

	if (!SelfActor || !BBComp)
	{
		return EBTNodeResult::Failed;
	}


	AC_BossRevenantAiController* AIController = Cast<AC_BossRevenantAiController>(SelfActor->GetController());
	if (AIController) AIController->BrainComponent->StopLogic("Dead");



	return EBTNodeResult::Aborted;
}
