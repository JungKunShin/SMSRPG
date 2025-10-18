// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "Widget/WC_SMSUserWidget.h"
#include "Widget/Party/WC_OnePartyWidget.h"
#include "WC_PartyWidget.generated.h"

class AC_PlayerCharacter;

UCLASS()
class STRONGMETALSTONE_API UWC_PartyWidget : public UWC_SMSUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void AddParty(AC_PlayerCharacter* Character);
	void ExitParty(FCharacterInfo CharacterInfo);

	void Update();
	void UpdateHp(AC_PlayerCharacter* PartyPlayer);
public:
	UPROPERTY()
	TArray<UWC_OnePartyWidget* >OnePartyWidgets;
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> OnePartyWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox_Party;


private:
	TArray<AC_PlayerCharacter*> PartyPlayers;
	

};
