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
		UCharacterMovementComponent* MovementComp = Warrior->GetCharacterMovement(); // CharacterMovement 저장
		if (!MovementComp) return;

		Warrior->Absolute = true;

		if (WPC->Subsystem)
		{
			WPC->Subsystem->RemoveMappingContext(WPC->MoveIMC); // Move IMC 제거
		}

		FVector ForwardVector = Warrior->GetActorForwardVector();
		
		DashDirection = ForwardVector; //무조건 캐릭터 앞방향으로 대쉬
		
		Warrior->LaunchCharacter(DashDirection * DASH_SPEED, true, true);

		//중력,마찰 끄기
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
			//MovementComp->Velocity = DashDirection * DASH_SPEED; //속도(방향) 계속 유지
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
			WPC->Subsystem->AddMappingContext(WPC->MoveIMC, 0); // MoveIMC 추가
			Warrior->ServerStopMontage(); // 몽타주 정지
		}		
		//중력,마찰복귀		
		Warrior->GetCharacterMovement()->GravityScale = 2.0f;
		Warrior->GetCharacterMovement()->GroundFriction = 8.0f; 
		Warrior->GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
		Warrior->GetCharacterMovement()->BrakingFriction = 8.0f;
	}
}
