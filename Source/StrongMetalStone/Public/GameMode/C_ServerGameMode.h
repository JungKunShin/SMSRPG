// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/C_SMSGameMode.h"
#include "C_ServerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_ServerGameMode : public AC_SMSGameMode
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	
	
	
};
