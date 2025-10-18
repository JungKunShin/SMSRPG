// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "C_WrKickAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrKickAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()
	
private:
	const float KNOCKBACK_STREANGTH = 1500.0f;

public:
	AC_WrKickAP();

protected:
	virtual void BeginPlay()override;

	UFUNCTION(Server,Reliable)
	void ServerKnockBack(AC_SMSCharacter*_HitEnemy);
};
