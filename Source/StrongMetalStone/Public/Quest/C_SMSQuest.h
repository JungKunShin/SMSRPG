// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../C_SMSStruct.h"
#include "Framework.h"
#include "C_SMSQuest.generated.h"

UCLASS()
class STRONGMETALSTONE_API AC_SMSQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_SMSQuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
	FQuestData QuestData;

	UPROPERTY()
	UDataTable* QuestDataTable;

	int32 ObjectNum; // Äù½ºÆ® ¸ñÇ¥ °¹¼ö

	FName QuestName;


};
