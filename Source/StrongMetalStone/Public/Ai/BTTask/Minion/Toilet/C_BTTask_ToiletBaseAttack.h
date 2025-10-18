// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask/Minion/C_BTTask_Minion.h"
#include "C_BTTask_ToiletBaseAttack.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTTask_ToiletBaseAttack : public UC_BTTask_Minion
{
	GENERATED_BODY()
	


protected:
	virtual AC_Enemy* GetEnemyCharacter(UBehaviorTreeComponent& OwnerComp) override;





};
