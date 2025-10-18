// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/PlayerCharacter/C_PlayerCharacterAnimInstance.h"
#include "C_WarriorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_WarriorAnimInstance : public UC_PlayerCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation()override;

	virtual void NativeUpdateAnimation(float DeltaSeconds)override;
};
