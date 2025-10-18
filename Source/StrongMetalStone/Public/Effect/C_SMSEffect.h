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
	EEffectType EffectType; //�����̻�Ÿ�� 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	float EffectTime = 3.0f; //���ӽð�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	UTexture2D* EffectImage; //����Ʈ �̹���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	float TickInterval = 1.0f; //�����̻� �ߵ� ƽ �ֱ�

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent; // �����̻� ���� ��ƼŬ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Emitter)
	UNiagaraSystem* EffectNiagara;

	FString EffectName;
};
