// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_WrBaseAttackSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrBaseAttackSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()
	
private:
	const float FIRST_COMBO_TIME = 0.75f;
	const float SECOND_COMBO_TIME = 0.55f;
	const float FIRST_ATTACK_RETURN = 0.4f;
	const float SECOND_ATTACK_RETURN = 0.3f;
	const float THIRD_ATTACK_RETURN = 0.63f;

public:
	virtual void StartOnce(AC_SMSCharacter* Character) override;
};
