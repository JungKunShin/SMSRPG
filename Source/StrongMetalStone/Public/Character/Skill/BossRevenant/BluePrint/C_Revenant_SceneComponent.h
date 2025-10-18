// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSActor.h"
#include "C_Revenant_SceneComponent.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_Revenant_SceneComponent : public AC_SMSActor
{
	GENERATED_BODY()
	


public:


	AC_Revenant_SceneComponent();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* WorldCenterPoint;

};
