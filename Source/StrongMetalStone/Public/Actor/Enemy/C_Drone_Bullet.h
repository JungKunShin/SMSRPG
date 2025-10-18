// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/C_SMSActor.h"
#include "C_Drone_Bullet.generated.h"

/**
 * 
 */
UCLASS()
class STRONGMETALSTONE_API AC_Drone_Bullet : public AC_SMSActor
{
	GENERATED_BODY()
	

public:

    AC_Drone_Bullet();

protected:

   
    //박스 콜리전
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* CollisionComp;


    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
