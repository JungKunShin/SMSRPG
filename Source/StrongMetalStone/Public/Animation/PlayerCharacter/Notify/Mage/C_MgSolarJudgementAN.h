// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotify.h"
#include "../../../../Actor/Projectile/Mage/C_MgSolarJudgetmentPr.h"
#include "C_MgSolarJudgementAN.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_MgSolarJudgementAN : public UC_SMSAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

	AC_MgSolarJudgetmentPr* SpawnedProjectile; // ������ AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>ProjectileClass; // �������Ʈ���� AP ������ â ����
};
