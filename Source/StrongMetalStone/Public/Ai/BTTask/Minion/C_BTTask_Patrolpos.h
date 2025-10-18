// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask/C_BTTask_Base.h"
#include "C_BTTask_Patrolpos.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTTask_Patrolpos : public UC_BTTask_Base
{
	GENERATED_BODY()
	


public:
	UC_BTTask_Patrolpos();

protected:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyHomepos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyPatrolpos;



	
};
