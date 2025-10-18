// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "C_CustomizingManager.generated.h"

class AC_PlayerCharacter;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_CustomizingManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	static void SetCustom(AC_PlayerCharacter* _Character, FCustomizingInfo _CustomInfo);

	UFUNCTION()
	static void SetArmorColor(AC_PlayerCharacter* _Character, int num);

	UFUNCTION()
	static void SetEyeColor(AC_PlayerCharacter* _Character, int num);

	UFUNCTION()
	static void SetEyeLashColor(AC_PlayerCharacter* _Character, int num);
	
	UFUNCTION()
	static void SetFaceColor(AC_PlayerCharacter* _Character, float value);
	
	UFUNCTION()
	static void SetHairColor(AC_PlayerCharacter* _Character, int num);
	
	UFUNCTION()
	static void SetWeaponColor(AC_PlayerCharacter* _Character, int num);

private:
	//전사 아머
	static void BasicChest(AC_PlayerCharacter*& _Character, FLinearColor Armor, FLinearColor Neck, FLinearColor Detail);
	static void BasicBelly(AC_PlayerCharacter*& _Character, FLinearColor Armor, FLinearColor Biceps, FLinearColor FormArm, FLinearColor Detail);
	static void BasicSkirt(AC_PlayerCharacter*& _Character, FLinearColor Armor, FLinearColor DetailUp, FLinearColor DetailDown, FLinearColor Point, FLinearColor Thigh);
	static void BasicKnee(AC_PlayerCharacter*& _Character,FLinearColor Armor, FLinearColor Leather, FLinearColor Detail);

	//마법사 옷
	static void BasicClothColor(AC_PlayerCharacter*& _Character, FLinearColor Fabric, FLinearColor Out,  FLinearColor Shirt,FLinearColor Skirt);
	static void BasicDetailColor(AC_PlayerCharacter*& _Character, FLinearColor Silk, FLinearColor Biz1, FLinearColor Biz2,FLinearColor Metal);

	//마법사 가방
	static void BasicBagColor(AC_PlayerCharacter*& _Character,FLinearColor Bag,FLinearColor Detail);
};
