// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_RidingAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_RidingAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation()override;

	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	class AC_SMSRiding* Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	class UCharacterMovementComponent* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float OwnerSpeed = 0;													// 캐릭터 걷기 속도

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	bool OnFalling;														// 공중여부
};
