// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotify.h"
#include "NiagaraSystem.h"
#include "C_FootStepAN.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_FootStepAN : public UC_SMSAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

	// 이펙트 시스템
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* NiagaraEffect;

	// 소켓 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FName SocketName = "head";

	// 이펙트 스케일
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FVector EffectScale = FVector(1.0f);
};
