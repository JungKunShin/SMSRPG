// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/C_DungeonGameMode.h"

void AC_DungeonGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AC_DungeonGameMode::LogOut(APlayerController* _NewPlayer, AC_PlayerCharacter* _Character)
{
	Super::LogOut(_NewPlayer, _Character);

	if(Players.IsEmpty())
	FGenericPlatformMisc::RequestExit(false);

}
