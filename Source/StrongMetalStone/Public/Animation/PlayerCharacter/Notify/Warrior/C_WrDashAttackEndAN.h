// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotify.h"
#include "../../../../Actor/AttackParticle/Warrior/C_WrDashAttackAP.h"
#include "C_WrDashAttackEndAN.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_WrDashAttackEndAN : public UC_SMSAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	AC_WrDashAttackAP* SpawnedAttackParticle; // ������ AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>AttackParticleClass;  // �������Ʈ���� AP ������ â ����
};
