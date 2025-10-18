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

    // �ڽ��� �������̵��ؼ� �ڽ��� BT/BB ��ȯ
    virtual UBehaviorTree* GetBehaviorTreeAsset() const { return nullptr; }
    virtual UBlackboardData* GetBlackboardAsset() const { return nullptr; }



};




