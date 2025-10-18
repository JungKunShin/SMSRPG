// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "C_DecalAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_DecalAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()

public:
	AC_DecalAP();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDecalComponent* DecalComp;
};
