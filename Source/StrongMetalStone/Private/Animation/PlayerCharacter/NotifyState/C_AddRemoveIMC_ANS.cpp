// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/C_AddRemoveIMC_ANS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_AddRemoveIMC_ANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;

	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Character->GetController());
	if (!WPC)return;

	if (WPC->Subsystem)
	{
		WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC); // 공격 IMC 제거
	}
}

void UC_AddRemoveIMC_ANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;

	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Character->GetController());
	if (!WPC)return;
	if (Character->CharacterInfo.Curhp <= 0)return;

	if (WPC->Subsystem)
	{
		WPC->Subsystem->AddMappingContext(WPC->AttackIMC, 0); // 공격 IMC 추가
	}
}
