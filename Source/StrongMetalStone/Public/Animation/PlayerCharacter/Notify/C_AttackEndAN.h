// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotify.h"
#include "C_AttackEndAN.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_AttackEndAN : public UC_SMSAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
