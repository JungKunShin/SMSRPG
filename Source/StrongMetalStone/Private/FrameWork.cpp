// Fill out your copyright notice in the Description page of Project Settings.


#include "FrameWork.h"

#include "Engine/World.h"
#include "GameMode/C_WorldGameMode.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Enemy.h"
#include "GameState/C_WorldGameState.h"
#include "HUD/C_WorldHUD.h"
#include "C_SMSGameInstance.h"
#include "PlayerState/C_WorldPlayerState.h"
#include "Character/C_Warrior.h"

AC_WorldGameMode* CastWGM(AGameModeBase* GM)
{
	return Cast<AC_WorldGameMode>(GM);
}

AC_WorldPlayerController* CastWPC(APlayerController* PC)
{
	return Cast<AC_WorldPlayerController>(PC);
}

AC_PlayerCharacter* CastWCharacter(AActor* Character)
{
	return Cast<AC_PlayerCharacter>(Character);
}

AC_Enemy* CastWEnemy(AActor* Enemy)
{
	return Cast<AC_Enemy>(Enemy);
}

AC_WorldGameState* CastWGS(AGameStateBase* GS)
{
	return Cast<AC_WorldGameState>(GS);
}

AC_WorldHUD* CastWHUD(AHUD* WHUD)
{
	return Cast<AC_WorldHUD>(WHUD);
}

AC_WorldPlayerState* CastWPS(APlayerState* PS)
{
	return Cast<AC_WorldPlayerState>(PS);
}

UC_SMSGameInstance* CastWGI(UGameInstance* GI)
{
	return Cast<UC_SMSGameInstance>(GI);
}

AC_Warrior* CastWWarrior(AActor* Character)
{
	return Cast<AC_Warrior>(Character);
}

FString GetLevelIP(int PortNum)
{
	FString MyLevelIP = GetServerIP();
	MyLevelIP.Append(":");
	MyLevelIP.AppendInt(PortNum);

	return MyLevelIP;
}
