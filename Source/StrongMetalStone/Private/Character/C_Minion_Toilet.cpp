// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_Minion_Toilet.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Ai/C_MinionAiController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"
#include "NiagaraFunctionLibrary.h" 
#include "NiagaraComponent.h"
AC_Minion_Toilet::AC_Minion_Toilet()
{
    EnemyInfo.Name = TEXT("고급 좌변기");
}

float AC_Minion_Toilet::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


    

    // 예시: 플레이어 캐릭터인지 확인
    AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(DamageCauser);
    if (Player)
    {

       // UE_LOG(LogTemp, Warning, TEXT("Player %s For me Damage Attake"), *Player->GetName());

       // UE_LOG(LogTemp, Warning, TEXT("player atk: %f"), Player->CharacterInfo.Damage);

        AC_MinionAiController* MinionAiController = Cast<AC_MinionAiController>(GetController());
        if (!MinionAiController) return DamageAmount;

        UBlackboardComponent* BBComp = MinionAiController->GetBlackboardComponent();
        if (!BBComp) return DamageAmount;

        BBComp->SetValueAsFloat(TEXT("TimeSinceLastAttack"), 0.0f);

        // 블랙보드에 있는 타겟 가져오기
        AActor* BBTarget = Cast<AActor>(BBComp->GetValueAsObject(TEXT("Target")));

        // 블랙보드 상의 타겟도 없고, 내부 변수도 nullptr이면 새로 설정
        if (BBTarget == nullptr || CurrentTarget == nullptr)
        {
            CurrentTarget = Player;
            BBComp->SetValueAsObject(TEXT("Target"), Player);
        }
    }
    return DamageAmount;
}

void AC_Minion_Toilet::BeginPlay()
{
    Super::BeginPlay();

    // 시작 시 원래 머티리얼 저장
    if (GetMesh())
    {
        OriginalMaterial = GetMesh()->GetMaterial(0);
    }

}

void AC_Minion_Toilet::Multicast_SpawnExplosionFX_Implementation()
{

    ExplosionNiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
        ExplosionNiagara,  // 이펙트 시스템
        this->GetMesh(), //타겟
        "head", //소켓
        this->GetActorLocation(),     // 상대 위치
        FRotator::ZeroRotator,   // 상대 회전
        EAttachLocation::KeepWorldPosition,
        false
    );

    if (ExplosionNiagaraComp)
    {
        ExplosionNiagaraComp->SetWorldScale3D(FVector(0.1f)); // 원하는 스케일로 설정
    }




    if (ExplosionSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(),CastWPC(GetMyPC())->SoundManager->EffectVolume);
    }





}

void AC_Minion_Toilet::HandleBlink()
{
    Multicast_Blink();
}

void AC_Minion_Toilet::StopBlink()
{
    GetWorldTimerManager().ClearTimer(BlinkTimerHandle);
    SetBlinkMaterial(OriginalMaterial);

    FVector SpawnLocation = GetActorLocation();


    Multicast_SpawnExplosionFX();
    

    SetLifeSpan(3.0f);

}

void AC_Minion_Toilet::SetBlinkMaterial(UMaterialInterface* NewMat)
{
    if (GetMesh() && NewMat)
    {
        GetMesh()->SetMaterial(0, NewMat);
    }
}

void AC_Minion_Toilet::Server_StartBlink_Implementation()
{

    GetWorldTimerManager().SetTimer
    (
        BlinkTimerHandle,      // [1] 핸들: 나중에 타이머를 종료하거나 확인할 때 사용
        this,                  // [2] 실행 주체 (보통 이 클래스의 this 포인터)
        &AC_Minion_Toilet::HandleBlink, // [3] 실행할 함수 포인터
        0.1f,                  // [4] 호출 간격 (초 단위)
        true                   // [5] 반복 여부 (true = 루프 실행)
    );


}

void AC_Minion_Toilet::Multicast_Blink_Implementation()
{
    if (!GetMesh()) return;

    UMaterialInterface* CurrentMaterial = GetMesh()->GetMaterial(0);
    if (CurrentMaterial == BlinkMaterial)
    {
        SetBlinkMaterial(OriginalMaterial);
    }
    else
    {
        SetBlinkMaterial(BlinkMaterial);
    }
}
