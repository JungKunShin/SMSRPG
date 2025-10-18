// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/C_Minion_UDHorse_AnimInstance.h"
#include "Character/C_UndeadHorse.h"




void UC_Minion_UDHorse_AnimInstance::NativeInitializeAnimation()
{

	Super::NativeInitializeAnimation();

	Enemy = Cast<AC_UndeadHorse>(GetOwningActor());		//PlayerCharacter�� ����ȯ
	if (Enemy)
	{
		Movement = Enemy->GetCharacterMovement();			//Owner�� Movement����
	}





}





void UC_Minion_UDHorse_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{


	Super::NativeUpdateAnimation(DeltaSeconds);




}
