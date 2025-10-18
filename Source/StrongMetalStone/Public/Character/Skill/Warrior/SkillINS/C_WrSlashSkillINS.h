// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_WrSlashSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrSlashSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()
	
private:
	const float COMBO_RESET_TIME = 2.0f;
	const float ATTACK_RETURN = 1.62f;

public:
	AC_WrSlashSkillINS();

	virtual void StartOnce(AC_SMSCharacter* Character)override;
};
