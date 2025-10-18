// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSProjectile.h"
#include "../../../Actor/AttackParticle/C_DecalAP.h"
#include "C_MgSolarJudgetmentPr.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_MgSolarJudgetmentPr : public AC_SMSProjectile
{
	GENERATED_BODY()
	
public:
	AC_MgSolarJudgetmentPr();

protected:
	virtual void BeginPlay()override;

	virtual void OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;

	void AttackDecal();

	AC_DecalAP* SpawnedDecal; // ������ AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>DecalClass; // �������Ʈ���� AP ������ â ����
};
