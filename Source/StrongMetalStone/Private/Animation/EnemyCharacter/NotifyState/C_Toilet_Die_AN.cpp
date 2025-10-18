// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Toilet_Die_AN.h"
#include "Character/C_Minion_Toilet.h"
#include "Character/C_PlayerCharacter.h"

void UC_Toilet_Die_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{



	AC_Minion_Toilet* Toilet = Cast<AC_Minion_Toilet>(MeshComp->GetOwner());

	if (!Toilet)return;


	// 서버인지 체크 
	if (!Toilet->HasAuthority())
	{
		return;
	}
	
	// 깜빡이는 머티리얼 실행
	Toilet->Server_StartBlink();


	FTimerHandle TempHandle;
	MeshComp->GetWorld()->GetTimerManager().SetTimer(
		TempHandle,
		FTimerDelegate::CreateUObject(Toilet, &AC_Minion_Toilet::StopBlink),
		5.0f,
		false
	);










}
