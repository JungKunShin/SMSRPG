// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSActor.h"
#include "AttackParticle/C_AttackImpactAP.h"
#include "C_SMSProjectile.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_SMSProjectile : public AC_SMSActor
{
	GENERATED_BODY()

public:
	AC_SMSProjectile();

protected:
	void DestroySelf();
	virtual void BeginPlay()override;

	UFUNCTION(Server, Reliable)
	void ServerDestroySelf();

	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(AActor* _HitActor, AC_PlayerCharacter* _Owner, float _Damage, FHitResult _Hit);

	UFUNCTION()
	virtual void OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(VisibleAnywhere, Category = Emitter)
	UParticleSystemComponent* EffectComponent; // 파티클 설정란

	UPROPERTY(VisibleAnywhere, Category = Scene)
	USceneComponent* SceneComponent; // 씬컴포넌트(루트역할)

	AC_PlayerCharacter* Owner;

	FTimerHandle DestroyTimerHandle; // AP 파괴 타이머핸들		

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage = 1.0f; // 기본 데미지 1.0
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DelayTime = 1.0f; // 기본 파괴 시간
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ShakeDegree = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AC_SMSEffectINS> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	class USphereComponent* AttackCollision;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	AC_AttackImpactAP* SpawnedAttackImpact; // 소환할 AP

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor>AttackImpactClass; // 블루프린트에서 설정할 AP

	// 폭발 사운드 (옵션)
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* BeginSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* AttenuationSetting;
};
