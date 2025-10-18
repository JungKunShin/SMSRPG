// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_Blacksmith.h"
#include "HUD/C_WorldHUD.h"

void AC_Blacksmith::Action(AC_PlayerCharacter* Character)
{
	if (AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{		
		WorldHUD->SetBlackSmithWidgetVisible(true);
		WorldHUD->SetInventoryWidgetVisible(true);
	}
}
