// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/BTTask/C_BTTask_Base.h"
#include "C_BTTask_Minion.generated.h"
class AC_Enemy;

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTTask_Minion : public UC_BTTask_Base
{
	GENERATED_BODY()
	
public:

	UC_BTTask_Minion();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	// 자식이 오버라이드 할 함수
	virtual AC_Enemy* GetEnemyCharacter(UBehaviorTreeComponent& OwnerComp);

	UPROPERTY()
	UBehaviorTreeComponent* CachedOwnerComp;

	UPROPERTY()
	AC_Enemy* SelfActor;

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	bool bAttackStarted;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyTimeSinceLastAttack;




};
