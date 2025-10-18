// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_NonPlayerCharacter.h"
#include "C_HunterMaker.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_HunterMaker : public AC_NonPlayerCharacter
{
	GENERATED_BODY()
	
public:
	virtual void Action(AC_PlayerCharacter* Character)override;
};
