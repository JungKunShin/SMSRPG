// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/C_PlayerCharacter.h"
#include "C_Mage.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_Mage : public AC_PlayerCharacter
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay()override;

public:
	AC_Mage();

	virtual void Death(AC_SMSCharacter*Killer)override;

	virtual void SetColor()override;

	virtual void NewColor(float Value)override;

	virtual void ButtonColor(FLinearColor Color, int32 Index)override;

	// ���� ���� (�ɼ�)
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	USoundBase* DeathSound;

	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialFace; // Ŀ���͸���¡ �󱼻� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialEye; // Ŀ���͸���¡ ���� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialHair1; // Ŀ���͸���¡ �Ӹ�ī����1 ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialHair2; // Ŀ���͸���¡ �Ӹ�ī����2 ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialEyeLash; // Ŀ���͸���¡ ����� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialJacket1; // Ŀ���͸���¡ ���ϻ� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialJacket2; // Ŀ���͸���¡ ���ϻ� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialJewelery; // Ŀ���͸���¡ ��ű��� ������ ���� MID

	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt1; // Ŀ���͸���¡ ��ű��� ������ ���� MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt2; // Ŀ���͸���¡ ��ű��� ������ ���� MID

	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialBag; // Ŀ���͸���¡ ����� ������ ���� MID

};
