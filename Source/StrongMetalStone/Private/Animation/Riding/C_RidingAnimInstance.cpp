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
			OwnerSpeed = UKismetMathLibrary::VSize(Movement->Velocity); //OwnerSpeed는 Movement의 속도 가져오기
		}
		else 
		{
			//GetCharacterMovement()->Velocity는 OwnerCharacter->GetVelocity()보다
			//복제된 이동 컴포넌트를 통해 보다 정확한 네트워크 상태를 반영
			FVector Velocity = Owner->GetCharacterMovement()->Velocity; 
			FVector HorizontalVelocity = FVector(Velocity.X, Velocity.Y, 0.f);
			OwnerSpeed = HorizontalVelocity.Size();
		}

		FVector Velocity = Owner->GetVelocity();
		Velocity.Z = 0.f; // 수직 속도 제거 (지상 이동만 고려)

		FVector Forward = Owner->GetActorForwardVector();
		Forward.Z = 0.f; // 수직 방향 제거		

		Velocity.Normalize();
		Forward.Normalize();

		if (FVector::DotProduct(Forward, Velocity) < 0.0f)
			OwnerSpeed *= -1.0f;


		OnFalling = Movement->IsFalling();							//Movement의 isfalling값 저장
	}
}
