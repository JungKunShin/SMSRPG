// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_FruitCollector.h"
#include "C_SMSGameInstance.h"

void AC_FruitCollector::Action(AC_PlayerCharacter* Character)
{
	CastWGI(GetMyGI())->QuestManager->PickUpInit(Character);
}
