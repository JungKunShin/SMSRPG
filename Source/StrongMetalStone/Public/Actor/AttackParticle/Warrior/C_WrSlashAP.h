// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "C_WrSlashAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrSlashAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()
	
public:
	AC_WrSlashAP();

protected:
	virtual void BeginPlay()override;
};
