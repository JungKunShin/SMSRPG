// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotify.h"
#include "NiagaraSystem.h"
#include "Manager/C_SoundManager.h"

#include "C_SoundNiagara_AN.generated.h"



/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_SoundNiagara_AN : public UC_SMSAnimNotify
{
	GENERATED_BODY()
	


public:

	// 이펙트 시스템
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* NiagaraEffect;

	// 사운드
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* Sound;

	// 사운드 감쇠 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* AttenuationSetting;

	// 소켓 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FName SocketName = "head";

	// 이펙트 스케일
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FVector EffectScale = FVector(1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	EVolumeType VolumeType = EVolumeType::Effect;

	//float GetVolumeValue(EVolumeType VolumeType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float NiagaraDestroyDelay = 3.0f;


	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;





};


