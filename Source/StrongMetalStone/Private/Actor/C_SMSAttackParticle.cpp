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
	bReplicates = true; // ���ø�����Ʈ true ����
	SetReplicateMovement(true); // Movement ���ø�����Ʈ�� true ����

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent")); // �� ����(��Ʈ��)
	RootComponent = SceneComponent; // �����۳�Ʈ ��Ʈ���۳�Ʈ�� ����

	EffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp")); // ����Ʈȿ��
	EffectComponent->SetupAttachment(SceneComponent);
}

void AC_SMSAttackParticle::ApplyDamage()
{
	TArray<FHitResult>HitResults; //Ʈ���̽� Hit�迭
	TSet<AActor*> AlreadyHitActors; //�ߺ����� ��Ʈ�� �迭
	//FVector Start = GetActorLocation(); // Ʈ���̽� ������
	//FVector End = Start; // Ʈ���̽� ������

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // AP �ڱ��ڽ� Ʈ���̽� ����

	// FriendlyAttack�� SphereMultiProfileƮ���̽� �߻�. Ʈ���̽��� �¾Ҵٸ� true
	bool bHit = GetWorld()->SweepMultiByProfile(HitResults, Start, End, FQuat::Identity, FName(TEXT("FriendlyAttack")), FCollisionShape::MakeSphere(SphereRadius), Params);

	//DrawDebugSphere(GetWorld(), Start, SphereRadius, 12, FColor::Red, false, 3.0f);
	//DrawDebugSphere(GetWorld(), End, SphereRadius, 12, FColor::Red, false, 3.0f);

	if (bHit)
	{
		for (const FHitResult Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();

			//�ڱ��ڽ��̸� return
			if (HitActor == Owner) return;

			if (HitActor && Cast<AC_SMSCharacter>(HitActor))
			{
				if (!AlreadyHitActors.Contains(HitActor))//�ߺ���Ʈ ����
				{
					AlreadyHitActors.Add(HitActor);
					//�� ������Ʈ Ÿ���� Enemy�̸�
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
	this->Destroy(); // �ڱ��ڽ� �ı��Լ�
}

void AC_SMSAttackParticle::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<AC_PlayerCharacter>(GetOwner());

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AC_SMSAttackParticle::DestroyDelay, DelayTime, false); // ������ DelayTime ��� �� �ı�

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

	UC_DamageManager::ApplyPointDamage(_HitActor, _Owner, _Damage, _Hit, EffectClass); //������ �����ϱ�
}
