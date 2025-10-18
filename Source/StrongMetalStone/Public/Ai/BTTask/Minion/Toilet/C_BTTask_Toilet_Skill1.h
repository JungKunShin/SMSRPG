// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask/Minion/C_BTTask_MinionSkill1.h"
#include "C_BTTask_Toilet_Skill1.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTTask_Toilet_Skill1 : public UC_BTTask_MinionSkill1
{
	GENERATED_BODY()
	

protected:
	virtual AC_Enemy* GetEnemyCharacterSkill1(UBehaviorTreeComponent& OwnerComp) override;

};
