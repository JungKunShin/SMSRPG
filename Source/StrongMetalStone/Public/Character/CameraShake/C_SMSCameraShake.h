// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include "Shakes/PerlinNoiseCameraShakePattern.h"
#include "C_SMSCameraShake.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_SMSCameraShake : public UCameraShakeBase
{
	GENERATED_BODY()
	
protected:
	UC_SMSCameraShake(const FObjectInitializer& ObjectInitializer);

	UPerlinNoiseCameraShakePattern* PerlinPattern;
};
