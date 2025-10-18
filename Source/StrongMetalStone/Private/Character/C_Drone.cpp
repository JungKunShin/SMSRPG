// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_Drone.h"

AC_Drone::AC_Drone()
{
    EnemyInfo.Name = TEXT("꼬마 드론");
}

void AC_Drone::Server_SpawnBullet_Implementation()
{


    FVector SpawnLocation = GetMesh()->GetSocketLocation("b_Gun");
    FRotator SpawnRotation = GetActorRotation();

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.Instigator = GetInstigator();

    if (BulletClass)  // 캐릭터에서 직접 설정된 총알 클래스
    {
        GetWorld()->SpawnActor<AActor>(BulletClass, SpawnLocation, SpawnRotation, Params);
    }


}

