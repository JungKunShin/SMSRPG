// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_SoundNiagara_AN.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundAttenuation.h"
#include "NiagaraComponent.h"
#include "Manager/C_SoundManager.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "UObject/WeakObjectPtr.h"
#include "UObject/WeakObjectPtrTemplates.h"

static float GetVolumeValue(EVolumeType VolumeType)
{
	auto* PC = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GWorld, 0));
	if (!PC) return 1.0f;

	auto* SM = CastWPC(PC)->SoundManager;
	if (!SM) return 1.0f;

	switch (VolumeType)
	{
	case EVolumeType::Master: return SM->MasterVolume;
	case EVolumeType::BGM:    return SM->BGMVolume;
	case EVolumeType::Effect: return SM->EffectVolume;
	case EVolumeType::UI:     return SM->UIVolume;
	default: return 1.0f;
	}
}


void UC_SoundNiagara_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

	if (!MeshComp) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	// 1. Niagara 이펙트 재생
	if (NiagaraEffect)
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			NiagaraEffect,
			MeshComp,
			SocketName,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTargetIncludingScale,
			true
		);

		if (NiagaraComp)
		{
			NiagaraComp->SetWorldScale3D(EffectScale);


			if (NiagaraComp && NiagaraDestroyDelay > 0.0f)
			{
				FTimerHandle TempHandle;

				TWeakObjectPtr<UNiagaraComponent> WeakNiagaraComp = NiagaraComp;

				Owner->GetWorldTimerManager().SetTimer(
					TempHandle,
					FTimerDelegate::CreateLambda([WeakNiagaraComp]()
						{
							if (WeakNiagaraComp.IsValid())
							{
								WeakNiagaraComp->DestroyComponent();
							}
						}),
					NiagaraDestroyDelay,
					false
				);

			}
		}
	}
	
	// 2. 사운드 재생
	if (Sound)
	{
		float Volume = GetVolumeValue(VolumeType);

		UGameplayStatics::PlaySoundAtLocation(
			Owner,
			Sound,
			Owner->GetActorLocation(),
			Volume,        // 선택한 볼륨 타입 적용됨
			1.0f,
			0.0f,
			AttenuationSetting
		);	
     }



}

