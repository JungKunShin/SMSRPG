// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "C_MgPlasmaDescentAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgPlasmaDescentAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()
	
private:
	const float UP_HEIGHT = 1000.0f;
	const float DOWN_HEIGHT = -100.0f;

public:
	AC_MgPlasmaDescentAP();

protected:
	virtual void BeginPlay()override;

	void DelayAttack();

	void AfterAttack();

private:
	FTimerHandle AttackTH;

	float AttackDelay = 1.2f;

	float AfterDelay = 0.1f;

public:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//UDecalComponent* DecalComp;
};
