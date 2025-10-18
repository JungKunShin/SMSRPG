// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_MgBaseAttackSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgBaseAttackSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()
	
private:
	const float FIRST_COMBO_TIME = 0.83f;
	const float FIRST_ATTACK_RETURN = 0.45f;
	const float SECOND_ATTACK_RETURN = 0.5f;

public:
	virtual void StartOnce(AC_SMSCharacter* Character);
};
