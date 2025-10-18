// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "C_MgHeliosAfterglowAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgHeliosAfterglowAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()

public:
	AC_MgHeliosAfterglowAP();

protected:
	virtual void BeginPlay()override;
};
