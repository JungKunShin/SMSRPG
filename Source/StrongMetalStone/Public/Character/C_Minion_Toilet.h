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

    /** ������ ���� - �������� ���� */
    UFUNCTION(Server, Reliable)
    void Server_StartBlink();

    /** ������ ���� - Ŭ�� ��ü */
    UFUNCTION(NetMulticast, Reliable)
    void Multicast_Blink();


    UFUNCTION(NetMulticast, Reliable)
    void Multicast_SpawnExplosionFX();




    /** ������ �ݺ� ���� */
    void HandleBlink();

    /** Ÿ�̸� ���� */
    void StopBlink();

    /** ��Ƽ���� ��ü */
    void SetBlinkMaterial(UMaterialInterface* NewMat);

    /** Ÿ�̸� �ڵ� */
    FTimerHandle BlinkTimerHandle;

    /** ���� ��Ƽ���� */
    UMaterialInterface* OriginalMaterial;

    /** �����ӿ� ��Ƽ���� */
    UPROPERTY(EditDefaultsOnly)
    UMaterialInterface* BlinkMaterial;

    // ���� FX ���� Ŭ����
  
    UPROPERTY(EditDefaultsOnly, Category = "Explosion")
    UNiagaraSystem* ExplosionNiagara;

    UPROPERTY(EditDefaultsOnly, Category = "Explosion")
    UNiagaraComponent* ExplosionNiagaraComp;


    // ���� ���� (�ɼ�)
    UPROPERTY(EditDefaultsOnly, Category = "Explosion")
    USoundBase* ExplosionSound;

  

};
