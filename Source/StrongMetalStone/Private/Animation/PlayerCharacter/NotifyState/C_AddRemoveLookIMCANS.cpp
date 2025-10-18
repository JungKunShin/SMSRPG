// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/C_AddRemoveLookIMCANS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_AddRemoveLookIMCANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;
	AC_PlayerCharacter* Character  = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Character->GetController());
	if (!WPC)return;

	if (WPC->Subsystem)
	{
		WPC->Subsystem->RemoveMappingContext(WPC->LookIMC); // LookIMC 제거
	}
}

void UC_AddRemoveLookIMCANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;
	AC_PlayerCharacter* Character = CastWCharacter(MeshComp->GetOwner());
	if (!Character)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Character->GetController());
	if (!WPC)return;
	if (Character->CharacterInfo.Curhp <= 0)return;

	if (WPC->Subsystem)
	{
		WPC->Subsystem->AddMappingContext(WPC->LookIMC, 0); // LookIMC 추가
	}
}
