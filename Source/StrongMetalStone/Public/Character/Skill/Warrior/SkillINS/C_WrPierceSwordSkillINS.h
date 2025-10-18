#pragma once

#include "CoreMinimal.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "C_WrPierceSwordSkillINS.generated.h"

UCLASS()
class STRONGMETALSTONE_API AC_WrPierceSwordSkillINS : public AC_SMSSkillINS
{
	GENERATED_BODY()
	
private:
	const float CHARGING_WALK_SPEED = 200.0f;

	const float FIRST_COMBO_TIME = 2.5f;
	const float SECOND_COMBO_TIME = 3.0f;
	const float THIRD_COMBO_TIME = 3.0f;

public:
	AC_WrPierceSwordSkillINS();

	virtual void StartOnce(AC_SMSCharacter* Character)override;
	virtual void EndHold(AC_SMSCharacter* Character)override; //¶­À»¶§

	void SecondCharge();
	void ThirdCharge();
	void OriginSpeedBack();

	float BasicWalkSpeed;

	FTimerHandle WalkSpeedTH;

private:
	bool bOnStart = false;

};
