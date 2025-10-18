// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotify.h"
#include "../../../../Actor/AttackParticle/Warrior/C_WrShieldAttackAP.h"
#include "C_WrShieldAttackAN.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_WrShieldAttackAN : public UC_SMSAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	AC_WrShieldAttackAP* SpawnedAttackParticle; // ������ AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>AttackParticleClass; // �������Ʈ���� AP ������ â ����
};
