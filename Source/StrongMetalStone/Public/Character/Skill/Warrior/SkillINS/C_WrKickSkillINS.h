// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_WrKickSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrKickSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()

private:
	const float ATTACK_RETURN = 1.2f;
	
public:

	virtual void StartOnce(AC_SMSCharacter* Character)override;
};
