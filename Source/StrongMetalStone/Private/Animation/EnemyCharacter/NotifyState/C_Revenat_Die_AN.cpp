// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Revenat_Die_AN.h"
#include "Character/C_RevenantBossCharacter.h"

void UC_Revenat_Die_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{




	AC_RevenantBossCharacter* RevenantBossCharacter = Cast<AC_RevenantBossCharacter>(MeshComp->GetOwner());

	if (!RevenantBossCharacter)return;


	// 서버인지 체크 
	if (!RevenantBossCharacter->HasAuthority())
	{
		return;
	}

	//
	RevenantBossCharacter->SetLifeSpan(2.0f);

}
