// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/C_Minion_UDHorse_AnimInstance.h"
#include "Character/C_UndeadHorse.h"




void UC_Minion_UDHorse_AnimInstance::NativeInitializeAnimation()
{

	Super::NativeInitializeAnimation();

	Enemy = Cast<AC_UndeadHorse>(GetOwningActor());		//PlayerCharacter로 형변환
	if (Enemy)
	{
		Movement = Enemy->GetCharacterMovement();			//Owner의 Movement저장
	}





}





void UC_Minion_UDHorse_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{


	Super::NativeUpdateAnimation(DeltaSeconds);




}
