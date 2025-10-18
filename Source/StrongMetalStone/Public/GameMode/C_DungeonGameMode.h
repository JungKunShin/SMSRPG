// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/C_WorldGameMode.h"
#include "C_DungeonGameMode.generated.h"

UCLASS()
class STRONGMETALSTONE_API AC_DungeonGameMode : public AC_WorldGameMode
{
	GENERATED_BODY()
protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void LogOut(APlayerController* _NewPlayer, AC_PlayerCharacter* _Character) override;
};
