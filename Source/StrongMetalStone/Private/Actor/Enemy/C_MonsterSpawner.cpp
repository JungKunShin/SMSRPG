// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Enemy/C_MonsterSpawner.h"
#include "Character/C_Minion.h"

AC_MonsterSpawner::AC_MonsterSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_MonsterSpawner::BeginPlay()
{
	Super::BeginPlay();



	if (!SpawnEnemy && HasAuthority())
		SpawnMonster();
}

void AC_MonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SpawnEnemy && HasAuthority() && !IsSpawning)
	{
		FTimerHandle SpawnTimerHandle;
		IsSpawning = true;		
		// 3초 뒤 재 소환
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AC_MonsterSpawner::SpawnMonster, SpawnTime, false);
	}
}

void AC_MonsterSpawner::SpawnMonster()
{
	float TempFloat = UKismetMathLibrary::RandomFloatInRange(-50.0f, 50.0f);
	float TempFloat2 = UKismetMathLibrary::RandomFloatInRange(-50.0f, 50.0f);

	FTransform TempTransform = GetActorTransform();
	FVector TempLocation =  FVector(TempTransform.GetLocation().X+ TempFloat, TempTransform.GetLocation().Y+ TempFloat2, GetActorLocation().Z + 150.0f);
	TempTransform.SetLocation(TempLocation);
	SpawnEnemy = GetWorld()->SpawnActor<AC_Minion>(SpawnEnemyClass, TempTransform);

	if (!SpawnEnemy)
	{
		FTimerHandle DelayTimerHandle;
		GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AC_MonsterSpawner::SpawnMonster, 0.1f, false);
		return;
	}
	SpawnEnemy->OwnerSpawner = this;
	IsSpawning = false;
}
