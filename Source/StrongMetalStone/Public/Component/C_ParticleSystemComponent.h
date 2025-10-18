// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/C_SMSActorComponent.h"
#include "../C_SMSEnum.h"
#include "C_ParticleSystemComponent.generated.h"

/**
 * 
 */

UCLASS()
class STRONGMETALSTONE_API UC_ParticleSystemComponent : public UC_SMSActorComponent
{
	GENERATED_BODY()
	
public:
	UC_ParticleSystemComponent();

protected:
	virtual void BeginPlay() override;

public:
	void CurHeat();

	UFUNCTION(Server,Reliable)
	void ServerUpdate();

	UFUNCTION(NetMulticast,Reliable)
	void MultiUpdate();

	void Update();
public:
	EOverHeat OverHeat;
};
