// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotify.h"
#include "../../../../Actor/AttackParticle/Mage/C_MgPlasmaDescentAP.h"
#include "C_MgPlasmaDescentAN.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_MgPlasmaDescentAN : public UC_SMSAnimNotify
{
	GENERATED_BODY()

private:
	const float FORWARD_DISTANCE = 700.0f;
	const float DOWN_HEIGHT = -80.0f;

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	
	AC_MgPlasmaDescentAP* SpawnedAttackParticle; // 스폰될 AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>AttackParticleClass; // 블루프린트에서 AP 설정할 창 열기
};
