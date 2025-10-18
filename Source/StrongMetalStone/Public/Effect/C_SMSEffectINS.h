// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SMSEffect.h"
#include "NiagaraComponent.h"
#include "C_SMSEffectINS.generated.h"

UCLASS()
class STRONGMETALSTONE_API AC_SMSEffectINS : public AActor
{
	GENERATED_BODY()

public:
	AC_SMSEffectINS();

	virtual void Start(AC_SMSCharacter* _Character); //상태이상 시작
	virtual void Tick(); //상태이상 지속
	virtual void End(); //상태이상 종료

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	UC_SMSEffect* EffectAsset;
	UPROPERTY(VisibleAnywhere, Category = Scene)
	USceneComponent* SceneComponent; // 씬컴포넌트(루트역할)

protected:
	AC_SMSCharacter* TargetCharacter;

private:
	FTimerHandle TickHandle;

	float EffectTimeRemaining = 0.0f; //남은 지속시간

	UPROPERTY()
	UNiagaraComponent* EffectNiagara;
};
