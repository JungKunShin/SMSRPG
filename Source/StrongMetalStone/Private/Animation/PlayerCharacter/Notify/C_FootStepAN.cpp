// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/C_FootStepAN.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_DungeonPlayerController.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

void UC_FootStepAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;

	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Character->GetController());
	if (!WPC)return;
	AC_DungeonPlayerController* DPC=Cast< AC_DungeonPlayerController>(Character->GetController());
	if (DPC)return;
	
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
		}
	}
}
