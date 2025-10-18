// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_Elder.h"
#include "C_SMSGameInstance.h"

void AC_Elder::Action(AC_PlayerCharacter* Character)
{
	CastWGI(GetMyGI())->QuestManager->DefeatBossInit(Character);
}
