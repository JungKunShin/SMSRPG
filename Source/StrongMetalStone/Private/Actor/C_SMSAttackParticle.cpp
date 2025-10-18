// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/C_SMSAttackParticle.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/C_Enemy.h"
#include "Effect/EffectINS/C_ElectricEffectINS.h"
#include "C_SMSGameInstance.h"
#include "Character/Skill/C_SMSSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Warrior.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Character/CameraShake/C_AttackCameraShake.h"
#include "Component/C_ParticleSystemComponent.h"

AC_SMSAttackParticle::AC_SMSAttackParticle()
{
	bReplicates = true; // 리플리케이트 true 설정
	SetReplicateMovement(true); // Movement 리플리케이트도 true 설정

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")); // 씬 생성(루트용)
	RootComponent = SceneComponent; // 씬컴퍼넌트 루트컴퍼넌트로 설정

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp")); // 이펙트효과
	EffectComponent->SetupAttachment(SceneComponent);
}

void AC_SMSAttackParticle::ApplyDamage()
{
	TArray<FHitResult>HitResults; //트레이스 Hit배열
	TSet<AActor*> AlreadyHitActors; //중복없는 히트된 배열
	//FVector Start = GetActorLocation(); // 트레이스 시작점
	//FVector End = Start; // 트레이스 종료점

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // AP 자기자신 트레이스 무시

	// FriendlyAttack형 SphereMultiProfile트레이스 발사. 트레이스에 맞았다면 true
	bool bHit = GetWorld()->SweepMultiByProfile(HitResults, Start, End, FQuat::Identity, FName(TEXT("FriendlyAttack")), FCollisionShape::MakeSphere(SphereRadius), Params);

	//DrawDebugSphere(GetWorld(), Start, SphereRadius, 12, FColor::Red, false, 3.0f);
	//DrawDebugSphere(GetWorld(), End, SphereRadius, 12, FColor::Red, false, 3.0f);

	if (bHit)
	{
		for (const FHitResult Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();

			//자기자신이면 return
			if (HitActor == Owner) return;

			if (HitActor && Cast<AC_SMSCharacter>(HitActor))
			{
				if (!AlreadyHitActors.Contains(HitActor))//중복히트 감지
				{
					AlreadyHitActors.Add(HitActor);
					//적 오브젝트 타입이 Enemy이면
					if (ECollisionChannel::ECC_GameTraceChannel1 == Cast<AC_SMSCharacter>(HitActor)->GetCapsuleComponent()->GetCollisionObjectType())
					{
						AC_WorldPlayerController* WorldController = Cast<AC_WorldPlayerController>(Owner->GetController());
						
						bOnHitEnemy = true;
						HitEnemies.Add(Cast<AC_SMSCharacter>(HitActor));
						if (GetMyCharacter()->IsLocallyControlled())
						{
							ServerApplyDamage(HitActor, Owner, Damage, Hit);
							if (!WorldController)return;
							WorldController->PlayerCameraManager->StartCameraShake(UC_AttackCameraShake::StaticClass(), ShakeDegree);
						}
						AC_Warrior* Warrior = Cast<AC_Warrior>(Owner);
						if (Warrior)
						{
							Warrior->DelayOverHeat();
						}
						if (AttackSound)
						{
							if (!WorldController)return;
							UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f, 0.0f, AttenuationSetting);
						}
					}
				}

			}

		}
	}
	/*DrawDebugSphere(GetWorld(), Start, SphereRadius,12,FColor::Red,false,2.0f);*/
}

void AC_SMSAttackParticle::DestroyDelay()
{
	this->Destroy(); // 자기자신 파괴함수
}

void AC_SMSAttackParticle::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AC_PlayerCharacter>(GetOwner());

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AC_SMSAttackParticle::DestroyDelay, DelayTime, false); // 설정한 DelayTime 경과 후 파괴

	AdjustAttack();

	Start = GetActorLocation();
	End = Start;

	if (Owner)
	{
		AC_WorldPlayerController* WorldController = Cast<AC_WorldPlayerController>(Owner->GetController());
		if (!WorldController)return;
		if (BeginSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, BeginSound, GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f,  0.0f, AttenuationSetting);
		}
	}

}

void AC_SMSAttackParticle::AdjustAttack()
{
	if (Cast<AC_Warrior>(Owner))
	{
		if (Owner->SkillSytemComponent->CurOverHeat == EOverHeat::LOWHEAT)
		{
			AdjustedAttackRate = LOW_RATE;
		}
		else if (Owner->SkillSytemComponent->CurOverHeat == EOverHeat::MIDDLEHEAT)
		{
			AdjustedAttackRate = MIDDLE_RATE;
		}
		else if (Owner->SkillSytemComponent->CurOverHeat == EOverHeat::HIGHHEAT)
		{
			AdjustedAttackRate = HIGH_RATE;
		}
	}
}

void AC_SMSAttackParticle::ServerApplyDamage_Implementation(AActor* _HitActor, AC_PlayerCharacter* _Owner, float _Damage, FHitResult _Hit)
{

	UC_DamageManager::ApplyPointDamage(_HitActor, _Owner, _Damage, _Hit, EffectClass); //데미지 수정하기
}
