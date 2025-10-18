// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_HunterMaker.h"
#include "C_SMSGameInstance.h"

void AC_HunterMaker::Action(AC_PlayerCharacter* Character)
{
	CastWGI(GetMyGI())->QuestManager->KillMonsterInit(Character);
}
