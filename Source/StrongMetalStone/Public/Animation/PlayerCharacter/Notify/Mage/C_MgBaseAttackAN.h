// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotify.h"
#include "../../../../Actor/Projectile/Mage/C_MgBaseAttackPr.h"
#include "C_MgBaseAttackAN.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_MgBaseAttackAN : public UC_SMSAnimNotify
{
	GENERATED_BODY()
	
private:
	const float SPAWNED_DISTANCE = 100.0f;
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

	AC_MgBaseAttackPr* SpawnedProjectile; // 스폰될 Projectile

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>ProjectileClass; // 블루프린트에서 AP 설정할 창 열기
};
