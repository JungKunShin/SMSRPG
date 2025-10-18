// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Enemy/C_Drone_Bullet.h"
#include "Components/BoxComponent.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Drone.h"

AC_Drone_Bullet::AC_Drone_Bullet()
{

    //  �ڽ� �ݸ��� ����
    CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
    RootComponent = CollisionComp;

    CollisionComp->InitBoxExtent(FVector(10.f, 10.f, 10.f));
    CollisionComp->SetCollisionProfileName("OverlapAll");
    CollisionComp->SetGenerateOverlapEvents(true);
    CollisionComp->SetNotifyRigidBodyCollision(false);

    // ������ ���ε�
    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AC_Drone_Bullet::OnOverlapBegin);

}

void AC_Drone_Bullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

    if (!HasAuthority()) return; // ���������� ����

    if (!OtherActor || OtherActor == GetOwner()) return;

    AC_Drone* Drone = Cast<AC_Drone>(GetOwner());

    AC_PlayerCharacter* HitCharacter = Cast<AC_PlayerCharacter>(OtherActor);
    if (HitCharacter)
    {

        // ���� ������ ó��
        
        FHitResult HitResult;
        //                                 ������ ,������ ,�������� ,�׳���Ʈ���, �����̻�ȿ��,
        UC_DamageManager::ApplyPointDamage(HitCharacter, Drone, (Drone->EnemyInfo.Damage)*10, HitResult);
        
    }



    Destroy(); // �� ���� �浹


}
