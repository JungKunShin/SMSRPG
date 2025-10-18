// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "../../../Actor/AttackParticle/C_AttackImpactAP.h"
#include "C_ParryingANS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_ParryingANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()
	
private:
	const float RUN_SPEED = 600.0f;
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ParryingSound;

	AC_AttackImpactAP* SpawnedImpact; // 스폰될 AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>ImpactClass; // 블루프린트에서 AP 설정할 창 열기
};
