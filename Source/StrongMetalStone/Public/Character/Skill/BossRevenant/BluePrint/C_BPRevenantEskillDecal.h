// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSActor.h"
#include "C_BPRevenantEskillDecal.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_BPRevenantEskillDecal : public AC_SMSActor
{
	GENERATED_BODY()
	

public:


    AC_BPRevenantEskillDecal();


    UPROPERTY(VisibleAnywhere)
    UDecalComponent* WarningDecal;


    UPROPERTY(VisibleAnywhere)
    UDecalComponent* AttackDecal;




};
