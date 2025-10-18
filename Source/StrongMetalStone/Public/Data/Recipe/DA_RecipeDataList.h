// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_RecipeDataList.generated.h"

class UDA_RecipeData;
/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UDA_RecipeDataList : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item List")
	TArray<UDA_RecipeData*> RecipeList;
	
	
};
