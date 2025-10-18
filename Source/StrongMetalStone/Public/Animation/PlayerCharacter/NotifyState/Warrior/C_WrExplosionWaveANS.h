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

	const float FIRST_SCALE = 5.0f; // 초기 스케일 값
	const float ADD_SCALE = 2.0f; // 증가 스케일 크기

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

	UFUNCTION()
	void SpawnDelayedActor(USkeletalMeshComponent* MeshComp);

	AC_WrExplosionWaveAP* SpawnedAttackParticle; // 소환할 AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>AttackParticleClass; // 블루프린트에서 설정할 AP

	FVector TotalScale = FVector(FIRST_SCALE, FIRST_SCALE, FIRST_SCALE); // 벡터값 초기스케일 값으로 저장

	FTimerHandle SpawnTimerHandle; // 스폰 딜레이 타이머 핸들
	FTimerHandle SpawnTimerHandle1;
	FTimerHandle SpawnTimerHandle2;
	FTimerHandle SpawnTimerHandle3;

	float Distance = 500.0f; // 초기 거리값
};
