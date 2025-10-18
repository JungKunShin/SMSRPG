// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask/C_BTTask_Base.h"
#include "C_BTTask_QSkill.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTTask_QSkill : public UC_BTTask_Base
{
	GENERATED_BODY()

public:
	UC_BTTask_QSkill();


protected:

	virtual EBTNodeResult::Type ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	// TickTask는 InProgress 리턴 시 매 Tick마다 호출됨
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool bSkillStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyMana;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyQSkillCooldown;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyOnQSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyCanAttack;

};
