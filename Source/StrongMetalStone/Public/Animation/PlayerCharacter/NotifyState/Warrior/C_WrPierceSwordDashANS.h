// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "C_WrPierceSwordDashANS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_WrPierceSwordDashANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;	
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

private:
	UPROPERTY()
	FVector DashDirection; // 대쉬방향
	UPROPERTY()
	AC_SMSCharacter* Target;
	UPROPERTY()
	float DashSpeed = 2500.0f;
};
