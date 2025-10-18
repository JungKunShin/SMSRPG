// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/C_WarriorAnimInstance.h"
#include "Character/C_Warrior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UC_WarriorAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<AC_Warrior>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UC_WarriorAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
