// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/C_SMSEffectINS.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Character/C_SMSCharacter.h"
#include "Components/SkeletalMeshComponent.h"

AC_SMSEffectINS::AC_SMSEffectINS()
{
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")); // �� ����(��Ʈ��)
    RootComponent = SceneComponent; // �����۳�Ʈ ��Ʈ���۳�Ʈ�� ����

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
            EffectAsset->EffectNiagara,  // ����Ʈ �ý���
            TargetCharacter->GetMesh(), //Ÿ��
            "HealthBar", //����
            FVector(0,0,20),     // ��� ��ġ
            FRotator::ZeroRotator,   // ��� ȸ��
            EAttachLocation::KeepRelativeOffset,
            false
        );

        //EffectNiagara->Activate(true);
        
    }


    if (TargetCharacter->GetMesh())
    {
        this->AttachToComponent(TargetCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
    }

    //ƽ �Լ�
    GetWorld()->GetTimerManager().SetTimer(TickHandle, this, &AC_SMSEffectINS::Tick, EffectAsset->TickInterval, true);

    //UI�߰��ϴ°� �� ����
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


    //���� UI���� �־��ٿ���
}
