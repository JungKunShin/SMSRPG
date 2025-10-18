// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/Minion/Toilet/C_BTTask_ToiletBaseAttack.h"
#include "Character/C_Minion_Toilet.h"
#include "AIController.h"



AC_Enemy* UC_BTTask_ToiletBaseAttack::GetEnemyCharacter(UBehaviorTreeComponent& OwnerComp)
{
	return Cast<AC_Minion_Toilet>(OwnerComp.GetAIOwner()->GetPawn());
}
