// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "C_BTTask_Base.generated.h"

class AC_PlayerCharacter;
	
class AC_Enemy;

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTTask_Base : public UBTTaskNode
{
	GENERATED_BODY()
	

protected:


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	virtual EBTNodeResult::Type ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);


	AC_Enemy* SelfActor;
	AC_PlayerCharacter* Target;
	UBlackboardComponent* BBComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeySelfActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyTarget;


};
