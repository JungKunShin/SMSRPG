// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/BossRevenant/BluePrint/C_Revenant_SceneComponent.h"

AC_Revenant_SceneComponent::AC_Revenant_SceneComponent()
{


    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));


    WorldCenterPoint = CreateDefaultSubobject<USceneComponent>(TEXT("WorldCenterPoint"));


    WorldCenterPoint->SetupAttachment(RootComponent);



}
