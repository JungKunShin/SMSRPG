// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/C_Minion_ToiletAniminstance.h"
#include "Character/C_Minion_Toilet.h"



void UC_Minion_ToiletAniminstance::NativeInitializeAnimation()
{

	Super::NativeInitializeAnimation();

	Enemy = Cast<AC_Minion_Toilet>(GetOwningActor());		//PlayerCharacter로 형변환
	if (Enemy)
	{
		Movement = Enemy->GetCharacterMovement();			//Owner의 Movement저장
	}
		

	

}

void UC_Minion_ToiletAniminstance::NativeUpdateAnimation(float DeltaSeconds)
{

	Super::NativeUpdateAnimation(DeltaSeconds);


}
