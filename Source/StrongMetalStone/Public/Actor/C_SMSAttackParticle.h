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
	UParticleSystemComponent* EffectComponent; // 파티클 설정란

	UPROPERTY(VisibleAnywhere, Category = Scene)
	USceneComponent* SceneComponent; // 씬컴포넌트(루트역할)

	AC_PlayerCharacter* Owner;


protected:
	void DestroyDelay();
	virtual void BeginPlay()override;

	UFUNCTION(Server,Reliable)
	void ServerApplyDamage(AActor* _HitActor, AC_PlayerCharacter* _Owner, float _Damage, FHitResult _Hit);

	void AdjustAttack();

	FTimerHandle DestroyTimerHandle; // AP 파괴 타이머핸들		

	float Damage = 1.0f; // 기본 데미지 1.0
	float SphereRadius = 150.0f; // 기본 트레이스 범위 1.5m
	float DelayTime = 1.0f; // 기본 파괴 시간

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<AC_SMSEffectINS> EffectClass;

	float ShakeDegree = 1.0f;
	float AdjustedAttackRate = 1.0f;

	bool bOnHitEnemy = false;
	AC_SMSCharacter* HitEnemy;
	TArray<AC_SMSCharacter*> HitEnemies;

	FVector Start;
	FVector End;

	// 폭발 사운드 (옵션)
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* BeginSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* AttenuationSetting;

};
