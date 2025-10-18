// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/BossRevenant/BluePrint/C_Revenant_Rskill_SceneActor.h"

AC_Revenant_Rskill_SceneActor::AC_Revenant_Rskill_SceneActor()
{



    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));


    WorldCenterPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WorldCenterPoint"));


    WorldCenterPoint->SetupAttachment(RootComponent);



}
