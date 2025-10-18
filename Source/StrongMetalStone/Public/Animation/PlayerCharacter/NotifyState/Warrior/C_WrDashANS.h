// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "C_WrDashANS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_WrDashANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()
	
private:
	float DASH_SPEED = 1800.0f; // 대쉬 속도
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

private:
	FVector DashDirection; // 대쉬방향
};
