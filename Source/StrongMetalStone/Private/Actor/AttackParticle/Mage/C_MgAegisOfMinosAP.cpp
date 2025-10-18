// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/Mage/C_MgAegisOfMinosAP.h"

AC_MgAegisOfMinosAP::AC_MgAegisOfMinosAP()
{
	Damage = 0.0f; // ������ 0.0
	SphereRadius = 1.0f; // Ʈ���̽� ���� ������ 1.5m
	DelayTime = 5.0f; // AP �ı� �ð�
	ShakeDegree = 0.5f; // ī�޶� ��鸲 ����

	DefenseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	DefenseMesh->SetupAttachment(EffectComponent);
	DefenseMesh->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel5);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMeshAsset.Succeeded())
	{
		DefenseMesh->SetStaticMesh(CubeMeshAsset.Object);
	}
}
