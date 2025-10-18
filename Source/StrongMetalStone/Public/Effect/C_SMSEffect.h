// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FrameWork.h"
#include "Character/C_PlayerCharacter.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "C_SMSEffect.generated.h"

/**
 *
 */
UCLASS()
class STRONGMETALSTONE_API UC_SMSEffect : public UDataAsset
{
	GENERATED_BODY()

public:
	UC_SMSEffect();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	EEffectType EffectType; //상태이상타입 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	float EffectTime = 3.0f; //지속시간

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	UTexture2D* EffectImage; //이펙트 이미지

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	float TickInterval = 1.0f; //상태이상 발동 틱 주기

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent; // 상태이상에 대한 파티클

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Emitter)
	UNiagaraSystem* EffectNiagara;

	FString EffectName;
};
