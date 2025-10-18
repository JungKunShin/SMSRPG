// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/C_SMSProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include"Components/SphereComponent.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Character/CameraShake/C_AttackCameraShake.h"

AC_SMSProjectile::AC_SMSProjectile()
{
	bReplicates = true; // 리플리케이트 true 설정
	SetReplicateMovement(true); // movement 리플리케이트도 true 설정


	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")); // 씬 생성(루트용)
	RootComponent = SceneComponent; // 씬컴퍼넌트 루트컴퍼넌트로 설정

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp")); // 이펙트효과
	EffectComponent->SetupAttachment(SceneComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollision"));
	AttackCollision->SetupAttachment(EffectComponent);
	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AC_SMSProjectile::OnAttackOverlap);
	AttackCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel5); //FriendlyAttack Collsion
}

void AC_SMSProjectile::DestroySelf()
{
	this->Destroy();
}

void AC_SMSProjectile::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AC_PlayerCharacter>(GetOwner());



	AC_WorldPlayerController* WorldController = Cast<AC_WorldPlayerController>(Owner->GetController());
	if (!WorldController)return;

	if (BeginSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, BeginSound, GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f,0.0f, AttenuationSetting);
	}
	WorldController->PlayerCameraManager->StartCameraShake(UC_AttackCameraShake::StaticClass(), ShakeDegree);

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AC_SMSProjectile::DestroySelf, DelayTime, false); // 설정한 DelayTime 경과 후 파괴

}

void AC_SMSProjectile::ServerDestroySelf_Implementation()
{
	this->Destroy();
}

void AC_SMSProjectile::ServerApplyDamage_Implementation(AActor* _HitActor, AC_PlayerCharacter* _Owner, float _Damage, FHitResult _Hit)
{
	UC_DamageManager::ApplyPointDamage(_HitActor, _Owner, _Damage, _Hit, EffectClass); //데미지 수정하기
}

void AC_SMSProjectile::OnAttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AC_SMSCharacter>(OtherActor))
	{
		if (ECollisionChannel::ECC_GameTraceChannel1 == Cast<AC_SMSCharacter>(OtherActor)->GetCapsuleComponent()->GetCollisionObjectType())
		{
			AC_WorldPlayerController* WorldController = Cast<AC_WorldPlayerController>(Owner->GetController());
			
			if (GetMyCharacter()->IsLocallyControlled())
			{
				ServerApplyDamage(OtherActor, Owner, Damage, SweepResult);
				ServerDestroySelf();
				SpawnedAttackImpact = GetWorld()->SpawnActor<AC_AttackImpactAP>(AttackImpactClass, GetActorLocation(), GetActorRotation()); // 액터 소환
			}
			if (HasAuthority())
			{
				//SpawnedAttackImpact = GetWorld()->SpawnActor<AC_AttackImpactAP>(AttackImpactClass, GetActorLocation(), GetActorRotation()); // 액터 소환
			}
			if (AttackSound)
			{
				if (!WorldController)return;
				UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f,0.0f, AttenuationSetting);
			}
		}
	}
}
