// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSActor.h"
#include "C_MonsterSpawner.generated.h"

class AC_Minion;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MonsterSpawner : public AC_SMSActor
{
	GENERATED_BODY()

protected:
	AC_MonsterSpawner();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;

	void SpawnMonster();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AC_Minion> SpawnEnemyClass;

	bool IsSpawning= false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SpawnTime = 5.0f;

public:
	UPROPERTY()
	AC_Minion* SpawnEnemy;
};
