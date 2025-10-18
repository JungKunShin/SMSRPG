// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask/C_BTTask_Base.h"
#include "C_BTTask_Dodge.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTTask_Dodge : public UC_BTTask_Base
{
	GENERATED_BODY()
	



public:

	UC_BTTask_Dodge();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	bool bSkillStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyOnDodgeSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyDodgeSkillCooldown;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyCanAttack;
};
