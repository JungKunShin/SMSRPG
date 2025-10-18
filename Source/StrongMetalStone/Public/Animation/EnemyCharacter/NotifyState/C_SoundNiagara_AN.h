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

	// ����Ʈ �ý���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* NiagaraEffect;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* Sound;

	// ���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* AttenuationSetting;

	// ���� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FName SocketName = "head";

	// ����Ʈ ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FVector EffectScale = FVector(1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	EVolumeType VolumeType = EVolumeType::Effect;

	//float GetVolumeValue(EVolumeType VolumeType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float NiagaraDestroyDelay = 3.0f;


	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;





};


