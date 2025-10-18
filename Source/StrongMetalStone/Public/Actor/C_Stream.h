// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSActor.h"
#include "C_Stream.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_Stream : public AC_SMSActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay()override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* BeginSound;

	// 사운드 감쇠 설정
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* AttenuationSetting;
};
