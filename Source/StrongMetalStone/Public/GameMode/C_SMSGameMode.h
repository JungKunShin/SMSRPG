// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FrameWork.h"
#include "C_SMSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_SMSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AC_PlayerCharacter> TestCharacterClass; //�׽�Ʈ��

	UPROPERTY(EditDefaultsOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AC_PlayerCharacter> Warrior; //����

	UPROPERTY(EditDefaultsOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AC_PlayerCharacter> Mage; //������

	UPROPERTY(EditDefaultsOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AC_PlayerCharacter> Healer; //����

};
