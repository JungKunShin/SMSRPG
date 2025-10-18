// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_PlayerCharacter.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "C_Warrior.generated.h"

/**
 * 
 */

UCLASS()
class STRONGMETALSTONE_API AC_Warrior : public AC_PlayerCharacter
{
	GENERATED_BODY()

private:
	AC_Warrior();

protected:
	virtual void BeginPlay()override;

public:
	virtual void Update()override;

	virtual void SetColor()override;
	virtual void NewColor(float Value)override; // Ŀ���͸���¡ �� ����(�����̴�)
	virtual void ButtonColor(FLinearColor Color, int32 Index)override;
	virtual float TakeDamage //�������� �ޱ�
	(
		float DamageAmount,						// ������ �� 
		struct FDamageEvent const& DamageEvent,	// ������ �̺�Ʈ
		class AController* EventInstigator,		// �������� �� ��Ʈ�ѷ�
		AActor* DamageCauser					// �������� �� ����
	) override;
	UFUNCTION()
	void OverHeatInit();
	void DelayOverHeat();
	UFUNCTION(Client,Reliable)
	void ClientDelayOverHeat();

	UFUNCTION(Server, Reliable)
	void ServerDelayOverHeat();

	virtual void Death(AC_SMSCharacter* Killer)override;
	void OnRiding();

	UFUNCTION(Server,Reliable)
	void ServerDelayUnBeatable();

	UFUNCTION(NetMulticast, Reliable)
	void MultiDelayUnBeatable();

	void UnBeatableInit();

	UFUNCTION(Server, Reliable)
	void ServerParrying();

	UFUNCTION(NetMulticast, Reliable)
	void MultiParrying();

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Effects")
	class UParticleSystemComponent* BodyParticle;

	int32 CameraIndex = 0;

public:
	bool OnTest = true;

	UPROPERTY(VisibleAnywhere, Category = Emitter)
	UNiagaraComponent* LowHeatEffects;
	UPROPERTY(VisibleAnywhere, Category = Emitter)
	UParticleSystemComponent* MiddleHeatEffects;
	UPROPERTY(VisibleAnywhere, Category = Emitter)
	UNiagaraComponent* HighHeatEffects;

	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialFace; // Ŀ���͸���¡ �󱼻� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialEye; // Ŀ���͸���¡ ���� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialHair; // Ŀ���͸���¡ �Ӹ�ī���� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialWeapon; // Ŀ���͸���¡ ����� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialEyeLash; // Ŀ���͸���¡ �Ӵ���� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt1; // Ŀ���͸���¡ �������ǻ� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt2; // Ŀ���͸���¡ �������ǻ� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt3; // Ŀ���͸���¡ �������ǻ� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt4; // Ŀ���͸���¡ �������ǻ� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt5; // Ŀ���͸���¡ �������ǻ� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt6; // Ŀ���͸���¡ �������ǻ� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialChest; // Ŀ���͸���¡ ���ʰ����κл� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialBelly; // Ŀ���͸���¡ ���ʹ�κл� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialKnee; // Ŀ���͸���¡ ���ʹ����κл� ������ ���� MID

	// ���� ���� (�ɼ�)
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	USoundBase* DeathSound;

	FTimerHandle UnBeatableTH;
};
