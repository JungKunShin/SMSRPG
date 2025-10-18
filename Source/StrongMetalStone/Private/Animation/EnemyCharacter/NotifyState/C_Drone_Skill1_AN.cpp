// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Drone_Skill1_AN.h"
#include "Character/C_Drone.h"
void UC_Drone_Skill1_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{



	AC_Drone* Drone = Cast<AC_Drone>(MeshComp->GetOwner());

	if (!Drone)return;


	// 서버인지 체크 
	if (!Drone->HasAuthority())
	{
		return;
	}


	// 해당 노티파이의 오너가 피가 1이상인지 체크
	if (Drone->EnemyInfo.Curhp <= 0.0f) return;



	Drone->Server_SpawnBullet();


}
