// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "C_WrPierceSwordAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrPierceSwordAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()
	
public:
	AC_WrPierceSwordAP();

protected:
	virtual void BeginPlay()override;

};
