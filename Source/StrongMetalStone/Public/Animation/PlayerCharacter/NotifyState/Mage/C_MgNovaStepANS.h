// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "../../../../Actor/Projectile/Mage/C_MgNovaStepPr.h"
#include "C_MgNovaStepANS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_MgNovaStepANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()
	
private:
	const float GAP_ANGLE = 20.0f;
	const float JUMP_HEIGHT = 600.0f;
	const float BACK_DISTANCE = -2000.0f;
public:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotlaDuration)override;

	UFUNCTION()
	void ProjectileSpawnFunc(USkeletalMeshComponent* MeshComp);

	AC_MgNovaStepPr* SpawnedProjectile; // 스폰될 AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>ProjectileClass; // 블루프린트에서 AP 설정할 창 열기

private:
	FTimerHandle SpawnTimerHandle;
};
