// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/Mage/C_MgManaChargeANS.h"
#include "Character/C_Mage.h"

void UC_MgManaChargeANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!MeshComp)return;

	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;
	if(Mage->CharacterInfo.Curmp< Mage->CharacterInfo.Maxmp)
	Mage->CharacterInfo.Curmp += 0.5f;
	Mage->Update();
}

void UC_MgManaChargeANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;

	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;

	if (Mage->SkillSytemComponent->CurSkill)
	{
		Mage->SkillSytemComponent->CurSkill->EndHold(Mage);
	}
}
