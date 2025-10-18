// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/C_ServerGameMode.h"
#include "HAL/PlatformMisc.h"

void AC_ServerGameMode::BeginPlay()
{
	Super::BeginPlay();

	//���𼭹� ����
	MakeServer("TitleLevel", 6773);
	MakeServer("WorldLevel", 6774);
	//MakeServer("OperaHouse1Level", 7780);
	
	FGenericPlatformMisc::RequestExit(false);
	

}


