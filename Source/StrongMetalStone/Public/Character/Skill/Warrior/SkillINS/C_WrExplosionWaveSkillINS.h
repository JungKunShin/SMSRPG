// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_WrExplosionWaveSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrExplosionWaveSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()

private:
	const float ATTACK_RETURN = 1.3f;

public:
	AC_WrExplosionWaveSkillINS();

	virtual void StartOnce(AC_SMSCharacter* Character) override;
};
