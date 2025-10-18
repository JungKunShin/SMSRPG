// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_Minion_Hostile.h"
#include "C_Drone.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_Drone : public AC_Minion_Hostile
{
	GENERATED_BODY()
	


public:
	AC_Drone();

	UFUNCTION(Server, Reliable)
	void Server_SpawnBullet();


	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AActor> BulletClass;


};
