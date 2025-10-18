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
	bReplicates = true; // ���ø�����Ʈ true ����
	SetReplicateMovement(true); // movement ���ø�����Ʈ�� true ����


	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")); // �� ����(��Ʈ��)
	RootComponent = SceneComponent; // �����۳�Ʈ ��Ʈ���۳�Ʈ�� ����

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp")); // ����Ʈȿ��
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

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AC_SMSProjectile::DestroySelf, DelayTime, false); // ������ DelayTime ��� �� �ı�

}

void AC_SMSProjectile::ServerDestroySelf_Implementation()
{
	this->Destroy();
}

void AC_SMSProjectile::ServerApplyDamage_Implementation(AActor* _HitActor, AC_PlayerCharacter* _Owner, float _Damage, FHitResult _Hit)
{
	UC_DamageManager::ApplyPointDamage(_HitActor, _Owner, _Damage, _Hit, EffectClass); //������ �����ϱ�
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
				SpawnedAttackImpact = GetWorld()->SpawnActor<AC_AttackImpactAP>(AttackImpactClass, GetActorLocation(), GetActorRotation()); // ���� ��ȯ
			}
			if (HasAuthority())
			{
				//SpawnedAttackImpact = GetWorld()->SpawnActor<AC_AttackImpactAP>(AttackImpactClass, GetActorLocation(), GetActorRotation()); // ���� ��ȯ
			}
			if (AttackSound)
			{
				if (!WorldController)return;
				UGameplayStatics::PlaySoundAtLocation(this, AttackSound, GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f,0.0f, AttenuationSetting);
			}
		}
	}
}
