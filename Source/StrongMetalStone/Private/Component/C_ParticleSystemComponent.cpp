// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/C_ParticleSystemComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Character/C_Warrior.h"
#include "UObject/ConstructorHelpers.h"

UC_ParticleSystemComponent::UC_ParticleSystemComponent()
{		
}

void UC_ParticleSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	AC_Warrior* Warrior = CastWWarrior(GetOwner());

	if (!Warrior)return;

	Warrior->LowHeatEffects->Deactivate();
	Warrior->MiddleHeatEffects->DeactivateSystem();
	Warrior->HighHeatEffects->Deactivate();
}

void UC_ParticleSystemComponent::CurHeat()
{
	AC_Warrior* Warrior = CastWWarrior(GetOwner());

	if (!Warrior)return;
	
	if (Warrior->CharacterInfo.Curmp == 0 && OverHeat!=EOverHeat::ZERO)
	{
		Warrior->LowHeatEffects->Deactivate();
		Warrior->MiddleHeatEffects->DeactivateSystem();
		Warrior->HighHeatEffects->Deactivate();
		OverHeat = EOverHeat::ZERO;
		
	}
	else if (Warrior->CharacterInfo.Curmp > 0&& Warrior->CharacterInfo.Curmp<=40&& OverHeat != EOverHeat::LOWHEAT)
	{
		Warrior->LowHeatEffects->Activate(true);
		Warrior->MiddleHeatEffects->DeactivateSystem();
		Warrior->HighHeatEffects->Deactivate();
		OverHeat = EOverHeat::LOWHEAT;
	}
	else if (Warrior->CharacterInfo.Curmp > 40&& Warrior->CharacterInfo.Curmp <=80 &&OverHeat != EOverHeat::MIDDLEHEAT)
	{
		Warrior->LowHeatEffects->Activate(true);
		Warrior->MiddleHeatEffects->ActivateSystem();
		Warrior->HighHeatEffects->Deactivate();
		OverHeat = EOverHeat::MIDDLEHEAT;
	}
	else if (Warrior->CharacterInfo.Curmp > 80 && Warrior->CharacterInfo.Curmp <= Warrior->CharacterInfo.Maxmp && OverHeat != EOverHeat::HIGHHEAT)
	{
		Warrior->LowHeatEffects->Activate(true);
		Warrior->MiddleHeatEffects->ActivateSystem();
		Warrior->HighHeatEffects->Activate(true);
		OverHeat = EOverHeat::HIGHHEAT;
	}

}

void UC_ParticleSystemComponent::ServerUpdate_Implementation()
{
	MultiUpdate();
}

void UC_ParticleSystemComponent::MultiUpdate_Implementation()
{
	CurHeat();
}
