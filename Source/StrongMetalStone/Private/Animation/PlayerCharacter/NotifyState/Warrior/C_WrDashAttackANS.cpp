// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/Warrior/C_WrDashAttackANS.h"
#include "Character/C_Warrior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_WrDashAttackANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;


	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;
	if (Warrior)
	{
		UCharacterMovementComponent* MovementComp = Warrior->GetCharacterMovement();//CharacterMovement ����
		if (!MovementComp) return;

		FVector ForwardVector = Warrior->GetActorForwardVector();
		FVector RightVector = Warrior->GetActorRightVector();
		FVector InputVector = Warrior->GetLastMovementInputVector();


		Target = Warrior->TargetCharacter;		
		if (!Target)return;

		FVector StartLocation = Warrior->GetActorLocation(); //������ġ
		FVector TargetLocation = Target->GetActorLocation(); //������ġ
		float Distance = FVector::Dist(StartLocation, TargetLocation); //����
		DashDirection = (TargetLocation - StartLocation).GetSafeNormal(); //�Ÿ�

		// ��� ���� �ð� ���
		float DashDuration = Distance / DASH_SPEED;

		MovementComp->GravityScale = 0.0f;
		// LaunchCharacter�� ���
		Warrior->LaunchCharacter(DashDirection * DASH_SPEED, true, true);

		FTimerHandle TimerHandle;
		Warrior->GetWorldTimerManager().SetTimer(TimerHandle, [Warrior, TargetLocation]()
			{
				Warrior->GetCharacterMovement()->StopMovementImmediately(); // ����
				Warrior->GetCharacterMovement()->GravityScale = 2.0f;

			}, DashDuration, false);
	}
}

void UC_WrDashAttackANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!MeshComp) return;

	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;
	if (Warrior)
	{
		UCharacterMovementComponent* MovementComp = Warrior->GetCharacterMovement();
		if (MovementComp)
		{
			//MovementComp->Velocity = DashDirection * DASH_SPEED; //�ӵ�(����) ��� ����
		}
	}
}
