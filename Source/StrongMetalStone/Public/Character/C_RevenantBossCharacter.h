// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_Boss.h"
#include "C_RevenantBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_RevenantBossCharacter : public AC_Boss
{
	GENERATED_BODY()
	

private:

	AC_RevenantBossCharacter();

	void QuestUpdate(AC_SMSCharacter* Killer);

public:
	virtual void Death(AC_SMSCharacter* Killer)override;

	UFUNCTION(NetMulticast,Reliable)
	void MultiDeath(AC_SMSCharacter* Killer);

	void OpenResult(AC_SMSCharacter* Killer);


	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	UPROPERTY(BlueprintReadWrite)
	bool Blocking = false;


};
