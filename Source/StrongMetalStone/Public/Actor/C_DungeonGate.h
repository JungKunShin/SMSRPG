// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSActor.h"
#include "Components/BoxComponent.h"
#include "C_DungeonGate.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_DungeonGate : public AC_SMSActor
{
	GENERATED_BODY()
	
private:
	AC_DungeonGate();

	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void BeginOverlapBoxCollision(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LevelName = "OperaHouseLevel1";	
	int32 PortNum = 6775;

};
