// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_Minion_Hostile.h"
#include "C_Undead.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_Undead : public AC_Minion_Hostile
{
	GENERATED_BODY()
	


public:
	AC_Undead();
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;


	// ��� �� ������ ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float BlockAccumulatedDamage = 0.0f;


	// �� ���������� �Ϸ��ߴ��� üũ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bParryFinishedClean = false;


};
