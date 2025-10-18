// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_MgHeliosAfterglowSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgHeliosAfterglowSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()
	
public:
	virtual void StartOnce(AC_SMSCharacter* Character) override; // ´­·¶À»¶§
	virtual void EndHold(AC_SMSCharacter* Character) override; // ¶­À»¶§

private:
	bool bOnStart = false;
};
