// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_Minion_Neutral.h"
#include "NiagaraSystem.h"

#include "C_Minion_Toilet.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_Minion_Toilet : public AC_Minion_Neutral
{
	GENERATED_BODY()
	

public:
    AC_Minion_Toilet();

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;
	




	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	AActor* CurrentTarget = nullptr;


    virtual void BeginPlay() override;

    /** 깜빡임 시작 - 서버에서 실행 */
    UFUNCTION(Server, Reliable)
    void Server_StartBlink();

    /** 깜빡임 실행 - 클라 전체 */
    UFUNCTION(NetMulticast, Reliable)
    void Multicast_Blink();


    UFUNCTION(NetMulticast, Reliable)
    void Multicast_SpawnExplosionFX();




    /** 깜빡임 반복 제어 */
    void HandleBlink();

    /** 타이머 종료 */
    void StopBlink();

    /** 머티리얼 교체 */
    void SetBlinkMaterial(UMaterialInterface* NewMat);

    /** 타이머 핸들 */
    FTimerHandle BlinkTimerHandle;

    /** 원래 머티리얼 */
    UMaterialInterface* OriginalMaterial;

    /** 깜빡임용 머티리얼 */
    UPROPERTY(EditDefaultsOnly)
    UMaterialInterface* BlinkMaterial;

    // 폭발 FX 액터 클래스
  
    UPROPERTY(EditDefaultsOnly, Category = "Explosion")
    UNiagaraSystem* ExplosionNiagara;

    UPROPERTY(EditDefaultsOnly, Category = "Explosion")
    UNiagaraComponent* ExplosionNiagaraComp;


    // 폭발 사운드 (옵션)
    UPROPERTY(EditDefaultsOnly, Category = "Explosion")
    USoundBase* ExplosionSound;

  

};
