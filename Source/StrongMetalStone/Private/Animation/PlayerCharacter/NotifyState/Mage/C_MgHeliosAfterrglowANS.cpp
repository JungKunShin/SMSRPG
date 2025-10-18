// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/Mage/C_MgHeliosAfterrglowANS.h"
#include "Character/C_Mage.h"

void UC_MgHeliosAfterrglowANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!MeshComp)return;

	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;

	if (Mage->HasAuthority())
	{
		FVector ForwardVector = MeshComp->GetOwner()->GetActorForwardVector();
		FVector SpawnLocation = Mage->GetActorLocation() + ForwardVector * 50.0f+FVector(0.0f,0.0f,50.0f);
		FRotator SpawnRotation = Mage->GetActorRotation() + FRotator(0.0f, 90.0f, 0.0f);

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Mage;
		SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_MgHeliosAfterglowAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam);
	}
}

void UC_MgHeliosAfterrglowANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;

	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;

	if (Mage->SkillSytemComponent->CurSkill)
	{
		//for (auto skill : Mage->SkillSytemComponent->EquipmentSkills)
		//{
		//	if (!skill.SkillData) return;

		/*	if (Mage->SkillSytemComponent->CurSkill->SkillAsset->SkillName == skill.SkillData->SkillName)
				skill.SkillInstance->EndHold(Mage);*/
		Mage->SkillSytemComponent->CurSkill->EndHold(Mage);
	}
}
