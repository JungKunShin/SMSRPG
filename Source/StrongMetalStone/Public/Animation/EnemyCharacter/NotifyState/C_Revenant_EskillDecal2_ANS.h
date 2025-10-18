// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_SMSAnimNotifyState.h"
#include "C_Revenant_EskillDecal2_ANS.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API UC_Revenant_EskillDecal2_ANS : public UC_SMSAnimNotifyState
{
	GENERATED_BODY()
	

public:

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<AActor> Revenant_BPEskillDecal;

	UPROPERTY()
	AActor* SpawnedDecalActor = nullptr;

	FVector StartScale = FVector::OneVector;
	FVector TargetScale = FVector::OneVector;
	float AccumulatedTime = 0.f;
	float Duration = 3.f; // 3초 동안 커지도록 설정

	

};
