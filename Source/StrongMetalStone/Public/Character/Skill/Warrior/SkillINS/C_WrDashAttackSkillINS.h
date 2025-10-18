// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_WrDashAttackSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrDashAttackSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()

private:
	const float ATTACK_RETURN = 1.4f;

public:
	AC_WrDashAttackSkillINS();

	virtual void StartOnce(AC_SMSCharacter* Character)override;

private:
	UPROPERTY()
	AC_SMSEffectINS* Effect;
};
