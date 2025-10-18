// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/EnemyCharacter/C_EnemyAniminstance.h"
#include "C_Minion_UDHorse_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_Minion_UDHorse_AnimInstance : public UC_EnemyAniminstance
{
	GENERATED_BODY()
	



public:
	virtual void NativeInitializeAnimation()override;

	virtual void NativeUpdateAnimation(float DeltaSeconds)override;





};
