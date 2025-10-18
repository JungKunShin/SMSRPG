// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "../../../../Actor/AttackParticle/Mage/C_MgHeliosAfterglowAP.h"
#include "C_MgHeliosAfterrglowANS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_MgHeliosAfterrglowANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
	
	AC_MgHeliosAfterglowAP* SpawnedAttackParticle; // 소환할 AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>AttackParticleClass; // 블루프린트에서 설정할 AP
};
