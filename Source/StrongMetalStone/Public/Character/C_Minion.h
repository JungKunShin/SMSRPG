// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_Enemy.h"
#include "Camera/CameraShake.h"

#include "C_Minion.generated.h"

class AC_MonsterSpawner;

UCLASS()
class STRONGMETALSTONE_API AC_Minion : public AC_Enemy
{
	GENERATED_BODY()
	

protected:
	virtual void Death(AC_SMSCharacter* Killer) override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	float AttackRange;

	UPROPERTY(BlueprintReadWrite)
	bool bIsBlocking = false;

	UPROPERTY()
	AC_MonsterSpawner* OwnerSpawner;


	UPROPERTY(EditAnywhere, Category = "CameraShake")
	TSubclassOf<UCameraShakeBase> CamShakeClass;


	UFUNCTION(Client, Reliable)
	void PlayCameraShake(AActor* DamageTarget);


};



