// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_QuestManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestChanged, AC_SMSQuest*, NewQuest);

class AC_PlayerCharacter;
class AC_SMSQuest;

UCLASS()
class STRONGMETALSTONE_API AC_QuestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_QuestManager();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnQuestChanged OnQuestChanged;

	void PickUpInit(AC_PlayerCharacter* Character);

	void KillMonsterInit(AC_PlayerCharacter* Character);

	void DefeatBossInit(AC_PlayerCharacter* Character);

public:
	UPROPERTY()
	AC_SMSQuest* CurQuest;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AC_SMSQuest> PickUp;
	UPROPERTY()
	AC_SMSQuest* PickUpINS;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AC_SMSQuest> KillMonster;
	UPROPERTY()
	AC_SMSQuest* KillMonsterINS;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AC_SMSQuest> DefeatBoss;
	UPROPERTY()
	AC_SMSQuest* DefeatBossINS;

	bool OnPickUp = true;
	bool OnKillMonster = true;
	bool OnDefeatBoss = true;
};
