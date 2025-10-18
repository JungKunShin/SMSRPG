// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSProjectile.h"
#include "C_MgNovaStepPr.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgNovaStepPr : public AC_SMSProjectile
{
	GENERATED_BODY()
	
public:
	AC_MgNovaStepPr();
protected:
	virtual void BeginPlay()override;

	virtual void OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
};
