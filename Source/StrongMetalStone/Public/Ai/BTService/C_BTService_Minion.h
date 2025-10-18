// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTService_Minion.generated.h"
class AC_PlayerCharacter;





/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_BTService_Minion : public UBTService
{
	GENERATED_BODY()
	

public:

	UC_BTService_Minion();


protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UFUNCTION()
	void DetectTargetEvent(AAIController* AIController, APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds);


	UFUNCTION()
	void SkillCoolTimeEvent(AAIController* AIController, APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds);


	UFUNCTION()
	AC_PlayerCharacter* FindTargetByTrace(AC_Minion* SelfActor);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyIsTaunt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyTauntCharacter;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyTimeSinceLastAttack;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyDistanceToTarget;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeySkillCoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyOnSkill;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeySkillCoolTime2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
	FBlackboardKeySelector KeyOnSkill2;
};
