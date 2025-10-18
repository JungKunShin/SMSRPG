// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "C_WrPierceSwordChargingANS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_WrPierceSwordChargingANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()

private:
	const float ADD_DEMANDED_MANA = 10.0f;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
};
