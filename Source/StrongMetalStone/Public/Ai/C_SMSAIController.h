// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FrameWork.h"
#include "C_SMSAIController.generated.h"


UCLASS()
class STRONGMETALSTONE_API AC_SMSAIController : public AAIController
{

	GENERATED_BODY()
	


protected:

   
    UBlackboardComponent* BBComp;

    virtual void OnPossess(APawn* InPawn) override;

    // 자식이 오버라이드해서 자신의 BT/BB 반환
    virtual UBehaviorTree* GetBehaviorTreeAsset() const { return nullptr; }
    virtual UBlackboardData* GetBlackboardAsset() const { return nullptr; }



};




