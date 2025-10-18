// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_ItemMaker.h"
#include "HUD/C_WorldHUD.h"

void AC_ItemMaker::Action(AC_PlayerCharacter* Character)
{
	if (AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD()))
	{
		WorldHUD->SetItemMakerWidgetVisible(true);
		WorldHUD->SetInventoryWidgetVisible(true);
		WorldHUD->InitRecipeGrid(DA_RecipeDataList);
	}
}
