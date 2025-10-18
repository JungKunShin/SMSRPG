// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/Warrior/C_WrDashANS.h"
#include "Character/C_Warrior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_WrDashANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;


	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;
	if (Warrior)
	{
		UCharacterMovementComponent* MovementComp = Warrior->GetCharacterMovement(); // CharacterMovement ����
		if (!MovementComp) return;

		Warrior->Absolute = true;

		if (WPC->Subsystem)
		{
			WPC->Subsystem->RemoveMappingContext(WPC->MoveIMC); // Move IMC ����
		}

		FVector ForwardVector = Warrior->GetActorForwardVector();
		
		DashDirection = ForwardVector; //������ ĳ���� �չ������� �뽬
		
		Warrior->LaunchCharacter(DashDirection * DASH_SPEED, true, true);

		//�߷�,���� ����
		MovementComp->GravityScale = 0.0f;
		Warrior->GetCharacterMovement()->GroundFriction = 0.0f;
		Warrior->GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
		Warrior->GetCharacterMovement()->BrakingFriction = 0.0f;
		
	}
}

void UC_WrDashANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
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

void UC_WrDashANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;

	Warrior->Absolute = false;

	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;
	if (Warrior)
	{
		if (WPC->Subsystem)
		{
			WPC->Subsystem->AddMappingContext(WPC->MoveIMC, 0); // MoveIMC �߰�
			Warrior->ServerStopMontage(); // ��Ÿ�� ����
		}		
		//�߷�,��������		
		Warrior->GetCharacterMovement()->GravityScale = 2.0f;
		Warrior->GetCharacterMovement()->GroundFriction = 8.0f; 
		Warrior->GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
		Warrior->GetCharacterMovement()->BrakingFriction = 8.0f;
	}
}
