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
	virtual void NewColor(float Value)override; // 커스터마이징 색 갱신(슬라이더)
	virtual void ButtonColor(FLinearColor Color, int32 Index)override;
	virtual float TakeDamage //데미지를 받기
	(
		float DamageAmount,						// 데미지 양 
		struct FDamageEvent const& DamageEvent,	// 데미지 이벤트
		class AController* EventInstigator,		// 데미지를 준 컨트롤러
		AActor* DamageCauser					// 데미지를 준 엑터
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
	UMaterialInstanceDynamic* DynMaterialFace; // 커스터마이징 얼굴색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialEye; // 커스터마이징 눈색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialHair; // 커스터마이징 머리카락색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialWeapon; // 커스터마이징 무기색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialEyeLash; // 커스터마이징 속눈썹색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt1; // 커스터마이징 갑옷하의색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt2; // 커스터마이징 갑옷하의색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt3; // 커스터마이징 갑옷하의색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt4; // 커스터마이징 갑옷하의색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt5; // 커스터마이징 갑옷하의색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt6; // 커스터마이징 갑옷하의색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialChest; // 커스터마이징 갑옷가슴부분색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialBelly; // 커스터마이징 갑옷배부분색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialKnee; // 커스터마이징 갑옷무릎부분색 변경을 위한 MID

	// 폭발 사운드 (옵션)
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	USoundBase* DeathSound;

	FTimerHandle UnBeatableTH;
};
