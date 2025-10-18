// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FrameWork.h"
#include "C_EnemyAniminstance.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_EnemyAniminstance : public UAnimInstance
{
	GENERATED_BODY()



protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	AC_Enemy* Enemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	float Speed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	float Direction = 0.f;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* SpawnAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	class UCharacterMovementComponent* Movement;

public:

	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;


};
