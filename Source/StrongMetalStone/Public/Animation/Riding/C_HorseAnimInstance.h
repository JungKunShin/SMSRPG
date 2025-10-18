// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/Riding/C_RidingAnimInstance.h"
#include "C_HorseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_HorseAnimInstance : public UC_RidingAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation()override;

	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
};
