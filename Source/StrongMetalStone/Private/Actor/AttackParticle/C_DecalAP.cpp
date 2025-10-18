// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/C_DecalAP.h"
#include"Components/DecalComponent.h"

AC_DecalAP::AC_DecalAP()
{
	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComp->SetupAttachment(RootComponent);
	DecalComp->SetVisibility(true);
}
