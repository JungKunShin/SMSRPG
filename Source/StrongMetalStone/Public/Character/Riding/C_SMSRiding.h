// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_SMSRiding.generated.h"

class AC_PlayerCharacter;

UCLASS()
class STRONGMETALSTONE_API AC_SMSRiding : public ACharacter
{
	GENERATED_BODY()

	const float RUN_SPEED = 1800.0f;
	const float WALK_SPEED = 1200.0f;
public:
	AC_SMSRiding();

	UFUNCTION(NetMulticast,Reliable)
	virtual void Mount(AC_PlayerCharacter* Rider);

	UFUNCTION(NetMulticast, Reliable)
	virtual void DisMount();

	void OnMount(AC_PlayerCharacter* Rider);

	void Move(FVector2D Value);

	void LookAt(FVector2D Value);

	UFUNCTION(Server,Reliable)
	void ServerRun();

	void Run();

public:
	UPROPERTY()
	AC_PlayerCharacter* CurrentRider;

protected:
	bool bOnRiding = false;

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* RidingBoom; // 탈것 카메라 스프링암

	UPROPERTY(VisibleAnywhere, BluePrintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* RidingCamera; // 탈것 카메라

	bool bOnRun = false;

public:
	// 파티 시스템
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UC_PartySystemComponent* PartySytemComponent;
};
