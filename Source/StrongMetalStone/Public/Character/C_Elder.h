// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_NonPlayerCharacter.h"
#include "C_Elder.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_Elder : public AC_NonPlayerCharacter
{
	GENERATED_BODY()
	
public:
	virtual void Action(AC_PlayerCharacter* Character)override;

};
