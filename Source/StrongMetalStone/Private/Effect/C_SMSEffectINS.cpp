// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/C_SMSEffectINS.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Character/C_SMSCharacter.h"
#include "Components/SkeletalMeshComponent.h"

AC_SMSEffectINS::AC_SMSEffectINS()
{
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")); // 씬 생성(루트용)
    RootComponent = SceneComponent; // 씬컴퍼넌트 루트컴퍼넌트로 설정

    EffectNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
    EffectNiagara->SetupAttachment(RootComponent);
    bReplicates = true;
}

void AC_SMSEffectINS::Start(AC_SMSCharacter* _Character)
{
    TargetCharacter = _Character;

    if (!EffectAsset)return;
    EffectTimeRemaining = EffectAsset->EffectTime;  

    if (EffectNiagara)
    {
        EffectNiagara = UNiagaraFunctionLibrary::SpawnSystemAttached(
            EffectAsset->EffectNiagara,  // 이펙트 시스템
            TargetCharacter->GetMesh(), //타겟
            "HealthBar", //소켓
            FVector(0,0,20),     // 상대 위치
            FRotator::ZeroRotator,   // 상대 회전
            EAttachLocation::KeepRelativeOffset,
            false
        );

        //EffectNiagara->Activate(true);
        
    }


    if (TargetCharacter->GetMesh())
    {
        this->AttachToComponent(TargetCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
    }

    //틱 함수
    GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &AC_SMSEffectINS::Tick, EffectAsset->TickInterval, true);

    //UI추가하는거 들어갈 예정
}

void AC_SMSEffectINS::Tick()
{
    EffectTimeRemaining -= EffectAsset->TickInterval;

    if (EffectTimeRemaining <= 0.0f)
    {
        End();
    }
}

void AC_SMSEffectINS::End()
{
    if (EffectNiagara)
    {
        EffectNiagara->DestroyComponent();
        EffectNiagara = nullptr;
    }
        
    if(TargetCharacter)
    TargetCharacter->CurEffects.Remove(EffectAsset->EffectName);

    this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    GetWorld()->GetTimerManager().ClearTimer(TickHandle);


    //여기 UI제거 넣어줄예정
}
