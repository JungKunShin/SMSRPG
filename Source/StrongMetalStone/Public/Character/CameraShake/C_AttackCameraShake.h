// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CameraShake/C_SMSCameraShake.h"
#include "C_AttackCameraShake.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_AttackCameraShake : public UC_SMSCameraShake
{
	GENERATED_BODY()
	
protected:
	UC_AttackCameraShake(const FObjectInitializer& ObjectInitializer);
};
