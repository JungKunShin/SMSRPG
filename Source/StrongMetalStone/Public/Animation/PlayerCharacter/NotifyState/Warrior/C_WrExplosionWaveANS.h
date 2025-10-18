// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "../../../../Actor/AttackParticle/Warrior/C_WrExplosionWaveAP.h"
#include "C_WrExplosionWaveANS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_WrExplosionWaveANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()
	
private:

	const float FIRST_SCALE = 5.0f; // �ʱ� ������ ��
	const float ADD_SCALE = 2.0f; // ���� ������ ũ��

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

	UFUNCTION()
	void SpawnDelayedActor(USkeletalMeshComponent* MeshComp);

	AC_WrExplosionWaveAP* SpawnedAttackParticle; // ��ȯ�� AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>AttackParticleClass; // �������Ʈ���� ������ AP

	FVector TotalScale = FVector(FIRST_SCALE, FIRST_SCALE, FIRST_SCALE); // ���Ͱ� �ʱ⽺���� ������ ����

	FTimerHandle SpawnTimerHandle; // ���� ������ Ÿ�̸� �ڵ�
	FTimerHandle SpawnTimerHandle1;
	FTimerHandle SpawnTimerHandle2;
	FTimerHandle SpawnTimerHandle3;

	float Distance = 500.0f; // �ʱ� �Ÿ���
};
