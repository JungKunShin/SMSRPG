// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Undead_Die_AN.h"
#include "Character/C_Undead.h"




void UC_Undead_Die_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{




	AC_Undead* Undead = Cast<AC_Undead>(MeshComp->GetOwner());

	if (!Undead)return;


	// �������� üũ 
	if (!Undead->HasAuthority())
	{
		return;
	}

	//
	Undead->SetLifeSpan(2.0f);



	

}
