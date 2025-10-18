// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_MgHeliosPulseSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgHeliosPulseSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()
	
private:
	const float ATTACK_RETURN = 1.9f;

public:
	AC_MgHeliosPulseSkillINS();

	virtual void StartOnce(AC_SMSCharacter* Character);
};
