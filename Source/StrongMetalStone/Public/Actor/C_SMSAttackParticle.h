// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSActor.h"
#include "Components/SceneComponent.h"
#include "../Effect/C_SMSEffectINS.h"
#include "../Character/CameraShake/C_AttackCameraShake.h"
#include "C_SMSAttackParticle.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_SMSAttackParticle : public AC_SMSActor
{
	GENERATED_BODY()
	
private:
	const float LOW_RATE = 1.2f;
	const float MIDDLE_RATE = 1.5f;
	const float HIGH_RATE = 2.5f;
public:
	AC_SMSAttackParticle();

	void ApplyDamage();
public:
	UPROPERTY(VisibleAnywhere, Category = Emitter)
	UParticleSystemComponent* EffectComponent; // ��ƼŬ ������

	UPROPERTY(VisibleAnywhere, Category = Scene)
	USceneComponent* SceneComponent; // ��������Ʈ(��Ʈ����)

	AC_PlayerCharacter* Owner;


protected:
	void DestroyDelay();
	virtual void BeginPlay()override;

	UFUNCTION(Server,Reliable)
	void ServerApplyDamage(AActor* _HitActor, AC_PlayerCharacter* _Owner, float _Damage, FHitResult _Hit);

	void AdjustAttack();

	FTimerHandle DestroyTimerHandle; // AP �ı� Ÿ�̸��ڵ�		

	float Damage = 1.0f; // �⺻ ������ 1.0
	float SphereRadius = 150.0f; // �⺻ Ʈ���̽� ���� 1.5m
	float DelayTime = 1.0f; // �⺻ �ı� �ð�

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<AC_SMSEffectINS> EffectClass;

	float ShakeDegree = 1.0f;
	float AdjustedAttackRate = 1.0f;

	bool bOnHitEnemy = false;
	AC_SMSCharacter* HitEnemy;
	TArray<AC_SMSCharacter*> HitEnemies;

	FVector Start;
	FVector End;

	// ���� ���� (�ɼ�)
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* BeginSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* AttenuationSetting;

};
