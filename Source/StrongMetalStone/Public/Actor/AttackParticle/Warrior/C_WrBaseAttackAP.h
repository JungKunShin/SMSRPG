// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "../../../Character/CameraShake/C_AttackCameraShake.h"
#include "C_WrBaseAttackAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrBaseAttackAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()

public:
	AC_WrBaseAttackAP();
	
protected:
	virtual void BeginPlay()override;
};
