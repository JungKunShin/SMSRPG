// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask/C_BTTask_Base.h"
#include "C_BTTask_Die.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTTask_Die : public UC_BTTask_Base
{
	GENERATED_BODY()


protected:

	virtual EBTNodeResult::Type ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
