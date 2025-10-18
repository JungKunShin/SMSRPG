// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FrameWork.h"
#include "C_PlayerCharacterAnimInstance.generated.h"

/**
 * 
 */


UCLASS()
class STRONGMETALSTONE_API UC_PlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation()override;

	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Character)
	class AC_PlayerCharacter* Owner;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Character)
	class UCharacterMovementComponent* Movement;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Character)
	float OwnerSpeed;													// ĳ���� �ȱ� �ӵ�

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Character)
	bool OnFalling;														// ���߿���
};
