// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Mage/C_MgAegisOfMinosAP.h"

AC_MgAegisOfMinosAP::AC_MgAegisOfMinosAP()
{
	Damage = 0.0f; // 데미지 0.0
	SphereRadius = 1.0f; // 트레이스 범위 반지름 1.5m
	DelayTime = 5.0f; // AP 파괴 시간
	ShakeDegree = 0.5f; // 카메라 흔들림 정도

	DefenseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	DefenseMesh->SetupAttachment(EffectComponent);
	DefenseMesh->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel5);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMeshAsset.Succeeded())
	{
		DefenseMesh->SetStaticMesh(CubeMeshAsset.Object);
	}
}
