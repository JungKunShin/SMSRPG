// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/C_ParryingUnbeatableANS.h"
#include "Character/C_PlayerCharacter.h"

void UC_ParryingUnbeatableANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;

	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	if (Character)
	{
		Character->Absolute = true;
	}
}

void UC_ParryingUnbeatableANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;

	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	if (Character)
	{
		Character->Absolute = false;
		Character->bOnShield = false;
		Character->bOnParrying = false;
	}
}
