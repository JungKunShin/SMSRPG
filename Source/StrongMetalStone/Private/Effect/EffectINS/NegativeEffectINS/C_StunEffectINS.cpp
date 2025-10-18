// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect/EffectINS/NegativeEffectINS/C_StunEffectINS.h"
#include "Character/C_PlayerCharacter.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

void AC_StunEffectINS::Start(AC_SMSCharacter* _Character)
{
	if (!Cast<AC_PlayerCharacter>(_Character))return;

	AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(_Character->GetController());
	
	if(Cast<AC_PlayerCharacter>(_Character)->CharacterInfo.Curhp>0&& Cast<AC_PlayerCharacter>(_Character)->bOnShield==false)
	_Character->ServerStopMontage();
	
	if (_Character->IsLocallyControlled())
	{
		if (Cast<AC_PlayerCharacter>(_Character)->bOnShield == false)
		{
			Cast<AC_PlayerCharacter>(_Character)->GetCharacterMovement()->StopMovementImmediately();
		}
		WPC->Subsystem->RemoveMappingContext(WPC->MoveIMC);
		WPC->Subsystem->RemoveMappingContext(WPC->LookIMC);
		WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
	}
	Super::Start(_Character);
}

void AC_StunEffectINS::Tick()
{
	AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(TargetCharacter->GetController());
	if (TargetCharacter->IsLocallyControlled())
	{
		if (Cast<AC_PlayerCharacter>(TargetCharacter)->bOnShield == false)
		{
			Cast<AC_PlayerCharacter>(TargetCharacter)->GetCharacterMovement()->StopMovementImmediately();
		}
		WPC->Subsystem->RemoveMappingContext(WPC->MoveIMC);
		WPC->Subsystem->RemoveMappingContext(WPC->LookIMC);
		WPC->Subsystem->RemoveMappingContext(WPC->AttackIMC);
	}
	//if (Cast<AC_PlayerCharacter>(TargetCharacter)->CharacterInfo.Curhp <= 0)
	//{
	//	TargetCharacter->ServerPlayMontage(TargetCharacter->DeathMontage);
	//	End();
	//	return;
	//}
	Super::Tick();
}

void AC_StunEffectINS::End()
{
	Super::End();

	if (TargetCharacter)
	{
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(TargetCharacter->GetController());
		if (TargetCharacter->IsLocallyControlled())
		{
			WPC->Subsystem->AddMappingContext(WPC->MoveIMC,0);
			WPC->Subsystem->AddMappingContext(WPC->LookIMC,0);
			WPC->Subsystem->AddMappingContext(WPC->AttackIMC,0);
		}
	}

}
