// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/BossRevenant/BluePrint/C_BPRevenantEskillDecal.h"
#include "Components/DecalComponent.h"



AC_BPRevenantEskillDecal::AC_BPRevenantEskillDecal()
{



    PrimaryActorTick.bCanEverTick = false;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    WarningDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("WarningDecal"));
    WarningDecal->SetupAttachment(RootComponent);
    WarningDecal->DecalSize = FVector(10.f, 10.f, 10.f);

    AttackDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("AttackDecal"));
    AttackDecal->SetupAttachment(RootComponent);
    AttackDecal->DecalSize = FVector(1.f, 1.f, 1.f);





}
