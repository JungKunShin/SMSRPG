// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/C_ParryingANS.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Warrior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_ParryingANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;

	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	if (Character)
	{
		Character->bOnParrying = true;
	}
}

void UC_ParryingANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!MeshComp)return;
	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	AC_Warrior* Warrior = Cast< AC_Warrior>(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Warrior->GetController());
	
	if (Character)
	{
		if (!Character->bOnParrying)
		{
			if (Warrior)
			{

				Warrior->ServerDelayUnBeatable();

				FVector ForwardVector = Warrior->GetActorForwardVector(); // 전사 앞방향 저장
				FVector RightVector = Warrior->GetActorRightVector();
				FVector SpawnLocation = Warrior->GetActorLocation() + ForwardVector * 80.0f+RightVector*-50.f; // 전사 위치에서 2미터 앞
				FRotator SpawnRotation = Warrior->GetActorRotation(); // 전사 각도 저장

				if (Warrior->HasAuthority()) // 서버에서만 소환
				{

					FActorSpawnParameters SpawnParam;
					SpawnParam.Owner = Warrior;
					SpawnedImpact = MeshComp->GetWorld()->SpawnActor<AC_AttackImpactAP>(ImpactClass, SpawnLocation, SpawnRotation, SpawnParam); // 액터 소환
				}
				if (ParryingSound)
				{
					if (!WPC)return;
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetOwner(), ParryingSound, SpawnLocation, WPC->SoundManager->EffectVolume, 1.0f);
				}
			}
		}
		Character->bOnParrying = true;
	}

}

void UC_ParryingANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;
	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	if (Character)
	{
		Character->bOnParrying = false;
	}
}
