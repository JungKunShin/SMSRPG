// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/C_PlayerCharacterAnimInstance.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UC_PlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<AC_PlayerCharacter>(GetOwningActor());		//PlayerCharacter�� ����ȯ
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();			//Owner�� Movement����
	}
}

void UC_PlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		OwnerSpeed = UKismetMathLibrary::VSize(Movement->Velocity); //OwnerSpeed�� Movement�� �ӵ� ��������
		OnFalling = Movement->IsFalling();							//Movement�� isfalling�� ����
	}
}
