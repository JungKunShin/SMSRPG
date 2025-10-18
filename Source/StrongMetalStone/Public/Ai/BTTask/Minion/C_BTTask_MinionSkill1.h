// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask/C_BTTask_Base.h"
#include "C_BTTask_MinionSkill1.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTTask_MinionSkill1 : public UC_BTTask_Base
{
	GENERATED_BODY()
	

public:

	UC_BTTask_MinionSkill1();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	// 자식이 오버라이드 할 함수
	virtual AC_Enemy* GetEnemyCharacterSkill1(UBehaviorTreeComponent& OwnerComp);

	UPROPERTY()
	UBehaviorTreeComponent* CachedOwnerComp;

	UPROPERTY()
	AC_Enemy* SelfActor;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	bool bAttackStarted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeySkillCoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyTimeSinceLastAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyOnSkill;




};
