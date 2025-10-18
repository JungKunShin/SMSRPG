// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "C_MgHeliosPulseAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgHeliosPulseAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()

private:
	const float KNOCKBACK_STREANGTH = 1200.0f;
	const float STRONGER_KNOCKBACK_STREANGTH = 1800.0f;
	const float CLOSE_RANGE = 500.0f;

public:
	AC_MgHeliosPulseAP();

protected:
	virtual void BeginPlay()override;

	UFUNCTION(Server, Reliable)
	void ServerKnockBack(AC_SMSCharacter* Character);

	void DelayAttack();

private:
	UPROPERTY(VisibleAnywhere, Category = Emitter)
	UNiagaraComponent* AttackEffects;

	float InitShakeDegree;

	FTimerHandle AttackTH;

	float AttackDelay = 1.0f;
};
