// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSActor.h"
#include "C_Revenant_Rskill_SceneActor.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_Revenant_Rskill_SceneActor : public AC_SMSActor
{
	GENERATED_BODY()
	


public:


	AC_Revenant_Rskill_SceneActor();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* WorldCenterPoint;
};
