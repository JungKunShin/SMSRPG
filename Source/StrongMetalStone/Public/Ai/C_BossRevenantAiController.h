// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ai/C_BossAiController.h"
#include "C_BossRevenantAiController.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_BossRevenantAiController : public AC_BossAiController
{
	GENERATED_BODY()
	


protected:
    UPROPERTY(EditAnywhere, Category = "AI")
    UBehaviorTree* BossBT;

    UPROPERTY(EditAnywhere, Category = "AI")
    UBlackboardData* BossBB;


public:
    virtual UBehaviorTree* GetBehaviorTreeAsset() const override { return BossBT; }

    virtual UBlackboardData* GetBlackboardAsset() const override { return BossBB; }


};
