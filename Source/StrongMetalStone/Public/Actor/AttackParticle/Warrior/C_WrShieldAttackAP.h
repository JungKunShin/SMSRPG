// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "C_WrShieldAttackAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrShieldAttackAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()
	
private:
	AC_WrShieldAttackAP();

	virtual void BeginPlay() override;
};
