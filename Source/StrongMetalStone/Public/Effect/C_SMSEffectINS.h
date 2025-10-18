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

	virtual void Start(AC_SMSCharacter* _Character); //�����̻� ����
	virtual void Tick(); //�����̻� ����
	virtual void End(); //�����̻� ����

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect)
	UC_SMSEffect* EffectAsset;
	UPROPERTY(VisibleAnywhere, Category = Scene)
	USceneComponent* SceneComponent; // ��������Ʈ(��Ʈ����)

protected:
	AC_SMSCharacter* TargetCharacter;

private:
	FTimerHandle TickHandle;

	float EffectTimeRemaining = 0.0f; //���� ���ӽð�

	UPROPERTY()
	UNiagaraComponent* EffectNiagara;
};
