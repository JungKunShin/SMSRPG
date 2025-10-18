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

	// 죽음 사운드 (옵션)
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	USoundBase* DeathSound;

	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialFace; // 커스터마이징 얼굴색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialEye; // 커스터마이징 눈색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialHair1; // 커스터마이징 머리카락색1 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialHair2; // 커스터마이징 머리카락색2 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialEyeLash; // 커스터마이징 눈썹색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialJacket1; // 커스터마이징 자켓색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialJacket2; // 커스터마이징 자켓색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialJewelery; // 커스터마이징 장신구색 변경을 위한 MID

	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt1; // 커스터마이징 장신구색 변경을 위한 MID
	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialSkirt2; // 커스터마이징 장신구색 변경을 위한 MID

	UPROPERTY()
	UMaterialInstanceDynamic* DynMaterialBag; // 커스터마이징 가방색 변경을 위한 MID

};
