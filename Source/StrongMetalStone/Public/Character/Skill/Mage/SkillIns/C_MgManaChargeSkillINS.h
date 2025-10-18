// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_MgManaChargeSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgManaChargeSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()
	
private:
	const float ATTACK_RETURN = 4.0f;

public:
	virtual void StartOnce(AC_SMSCharacter* Character)override;
	virtual void EndHold(AC_SMSCharacter* Character)override;

private:
	bool bOnStart = false;
};
