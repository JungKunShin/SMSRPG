// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Widget/WC_SMSUserWidget.h"
#include "FrameWork.h"
#include "../Widget/Ingame/WC_DeathWidget.h"

#include "C_SMSHUD.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_SMSHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void SetInputMode(EInputMode InputMode, bool ShowMouseCurSor);
	
	//À§Á¬ »ý¼º
	template <typename T>
	void CreateMyWidget(TSubclassOf<UUserWidget> WidgetClass, T*& Widget, ESlateVisibility Visibility = ESlateVisibility::Visible)
	{
		if (WidgetClass)
		{
			Widget = Cast<T>(CreateWidget<UUserWidget>(GetOwningPlayerController(), WidgetClass));
		}

		if (Widget)
		{
			Widget->AddToViewport();		
			Widget->SetVisibility(Visibility);
		}
	}

};  
