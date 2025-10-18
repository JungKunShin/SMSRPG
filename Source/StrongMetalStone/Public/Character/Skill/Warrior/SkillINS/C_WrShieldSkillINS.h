// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_WrShieldSkillINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_WrShieldSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()
	
private:
	const float CHARGING_WALK_SPEED = 200.0f;
public:
	virtual void StartOnce(AC_SMSCharacter* Character)override;
	virtual void Holding(AC_SMSCharacter* Character)override;
	virtual void EndHold(AC_SMSCharacter* Character)override; //¶­À»¶§

	float BasicWalkSpeed;

	FTimerHandle ShieldOffTH;
};
