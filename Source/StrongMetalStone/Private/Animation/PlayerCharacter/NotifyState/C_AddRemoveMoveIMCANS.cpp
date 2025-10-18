// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/C_AddRemoveMoveIMCANS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_AddRemoveMoveIMCANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;
	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Character->GetController());
	if (!WPC)return;

	if (WPC->Subsystem)
	{
		WPC->Subsystem->RemoveMappingContext(WPC->MoveIMC); // MoveIMC 제거
	}
}

void UC_AddRemoveMoveIMCANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;
	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Character->GetController());
	if (!WPC)return;
	if (Character->CharacterInfo.Curhp <= 0)return;

	if (WPC->Subsystem)
	{
		WPC->Subsystem->AddMappingContext(WPC->MoveIMC, 0); // MoveIMC 추가
	}
}
