// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Riding/C_RidingAnimInstance.h"
#include "Character/Riding/C_SMSRiding.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UC_RidingAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<AC_SMSRiding>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UC_RidingAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		if (Owner->IsLocallyControlled())
		{
			OwnerSpeed = UKismetMathLibrary::VSize(Movement->Velocity); //OwnerSpeed�� Movement�� �ӵ� ��������
		}
		else 
		{
			//GetCharacterMovement()->Velocity�� OwnerCharacter->GetVelocity()����
			//������ �̵� ������Ʈ�� ���� ���� ��Ȯ�� ��Ʈ��ũ ���¸� �ݿ�
			FVector Velocity = Owner->GetCharacterMovement()->Velocity; 
			FVector HorizontalVelocity = FVector(Velocity.X, Velocity.Y, 0.f);
			OwnerSpeed = HorizontalVelocity.Size();
		}

		FVector Velocity = Owner->GetVelocity();
		Velocity.Z = 0.f; // ���� �ӵ� ���� (���� �̵��� ���)

		FVector Forward = Owner->GetActorForwardVector();
		Forward.Z = 0.f; // ���� ���� ����		

		Velocity.Normalize();
		Forward.Normalize();

		if (FVector::DotProduct(Forward, Velocity) < 0.0f)
			OwnerSpeed *= -1.0f;


		OnFalling = Movement->IsFalling();							//Movement�� isfalling�� ����
	}
}
