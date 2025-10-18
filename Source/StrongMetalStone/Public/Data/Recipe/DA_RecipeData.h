// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FrameWork.h"
#include "DA_RecipeData.generated.h"

class UDA_ItemData;
/**
 * 
 */
UCLASS(BlueprintType)
class STRONGMETALSTONE_API UDA_RecipeData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//WC_ItemSlot을불러와야함
	UPROPERTY(EditAnywhere, BlueprintReadOnly)	
	TMap<TSubclassOf<UDA_ItemData>, int32>Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UDA_ItemData> ResultClass;
	
};
