// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/C_SMSAIController.h"
#include "C_MinionAiController.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MinionAiController : public AC_SMSAIController
{
	GENERATED_BODY()
	


protected:
    UPROPERTY(EditAnywhere, Category = "AI")
    UBehaviorTree* MinionBT;

    UPROPERTY(EditAnywhere, Category = "AI")
    UBlackboardData* MinionBB;


public:
    virtual UBehaviorTree* GetBehaviorTreeAsset() const override { return MinionBT; }

    virtual UBlackboardData* GetBlackboardAsset() const override { return MinionBB; }


};
