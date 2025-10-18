// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FrameWork.h"
#include "C_SMSAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_SMSAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	inline virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
