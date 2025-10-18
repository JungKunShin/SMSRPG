// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotify.h"
#include "../../../../Actor/AttackParticle/Mage/C_MgAegisOfMinosAP.h"
#include "C_MgAegisOfMinosAN.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_MgAegisOfMinosAN : public UC_SMSAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

	AC_MgAegisOfMinosAP* SpawnedAttackParticle; // 스폰될 AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>AttackParticleClass; // 블루프린트에서 AP 설정할 창 열기
};
