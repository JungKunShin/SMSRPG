// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "C_WrDashAttackANS.generated.h"

class AC_SMSCharacter;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_WrDashAttackANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()
	
private:
	const float DASH_SPEED = 4000.0f; // 대쉬 속도
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;

private:
	FVector DashDirection; // 대쉬방향

	AC_SMSCharacter* Target;
};
