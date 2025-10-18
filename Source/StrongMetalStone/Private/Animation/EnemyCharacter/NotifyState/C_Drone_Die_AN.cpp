// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Drone_Die_AN.h"
#include "Character/C_Drone.h"


void UC_Drone_Die_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{


	AC_Drone* Drone = Cast<AC_Drone>(MeshComp->GetOwner());

	if (!Drone)return;


	// �������� üũ 
	if (!Drone->HasAuthority())
	{
		return;
	}
		
	//
	Drone->SetLifeSpan(2.0f);



}
