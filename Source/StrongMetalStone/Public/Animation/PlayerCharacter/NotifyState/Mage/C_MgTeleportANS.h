// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "C_MgTeleportANS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_MgTeleportANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()
	
private:
	const float TELEPORT_DISTANCE = 1000.0f;
	const float TRACE_HEIGHT = 50.0f;
	const float BACK_DISTANCE = 50.0f;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

private:
	float CameraDistance;
	float OriginCameraDistance;
};
