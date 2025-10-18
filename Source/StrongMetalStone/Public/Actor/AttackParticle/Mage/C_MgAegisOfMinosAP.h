// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSAttackParticle.h"
#include "C_MgAegisOfMinosAP.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgAegisOfMinosAP : public AC_SMSAttackParticle
{
	GENERATED_BODY()
	
public:
	AC_MgAegisOfMinosAP();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shield)
	UStaticMeshComponent* DefenseMesh;
};
