// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_EffectManager.generated.h"

class AC_SMSCharacter;
class AC_SMSEffectINS;

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_EffectManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Effect")
	TSubclassOf<AC_SMSEffectINS> ElectricEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	TSubclassOf<AC_SMSEffectINS> StunEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	TSubclassOf<AC_SMSEffectINS> PowerStunEffectClass;
};
