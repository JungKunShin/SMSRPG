// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTService.h"
#include "C_BTService_Revenant.generated.h"
class AC_PlayerCharacter;
/**
 * 
 */

UCLASS()
class STRONGMETALSTONE_API UC_BTService_Revenant : public UBTService
{
	GENERATED_BODY()

public:

	    UC_BTService_Revenant();


protected:

		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


		UFUNCTION()
		void DetectTargetEvent(AAIController* AIController, APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds);

		UFUNCTION()
		void SelfHp(APawn* ControlledPawn, UBlackboardComponent* BBComp);

		UFUNCTION()
		void QSkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds);

		UFUNCTION()
		void WSkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds);

		UFUNCTION()
		void ESkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds);

		UFUNCTION()
		void RSkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds);


		UFUNCTION()
		void DodgeSkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds);



		float TimeSinceTargetSet = 0.0f;
		float MaxTargetHoldTime = 5.0f;

		// r ��ų ü�¿� ���� ����� �����Ҷ�
		bool UsedRSkill70 = false;
		bool UsedRSkill30 = false;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyTarget;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeySelfHp;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyMana;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeySelfGroogy;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyIsDead;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyHasGroogy;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyPhase1;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyIsTaunt;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyTauntCharacter;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyDistanceToTarget;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeybCanAttack;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyOnQSkill;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyQSkillCooldown;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyOnWSkill;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyWSkillCooldown;



		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyOnESkill;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyESkillCooldown;


		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyOnRSkill;

	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyOnDodgeSkill;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyName")
		FBlackboardKeySelector KeyDodgeSkillCooldown;


private:

	// Ÿ���� ��ȿ���� �˻� (�׾����� ���� Ȯ��)
	bool IsValidTarget(AC_PlayerCharacter* Target);

	// ������ �÷��̾ ��ȯ
	AC_PlayerCharacter* SelectRandomTarget(const TArray<AC_PlayerCharacter*>& Players);
	// ���� �ֺ����� ����ִ� �÷��̾ ����
	TArray<AC_PlayerCharacter*> PerformPlayerDetection(APawn* BossPawn);



};
