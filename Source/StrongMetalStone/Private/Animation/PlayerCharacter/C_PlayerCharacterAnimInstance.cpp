// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/C_PlayerCharacterAnimInstance.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UC_PlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<AC_PlayerCharacter>(GetOwningActor());		//PlayerCharacter로 형변환
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();			//Owner의 Movement저장
	}
}

void UC_PlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		OwnerSpeed = UKismetMathLibrary::VSize(Movement->Velocity); //OwnerSpeed는 Movement의 속도 가져오기
		OnFalling = Movement->IsFalling();							//Movement의 isfalling값 저장
	}
}
