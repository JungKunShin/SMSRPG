// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effect/C_SMSEffectINS.h"
#include "C_StunEffectINS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_StunEffectINS : public AC_SMSEffectINS
{
	GENERATED_BODY()
	
public:

	virtual void Start(AC_SMSCharacter* _Character); //�����̻� ����
	virtual void Tick(); //�����̻� ����
	virtual void End(); //�����̻� ����
};
